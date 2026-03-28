/*** Last Changed: 2026-03-28 - 16:09 ***/
#include <Arduino.h>
#include <Wire.h>
#include <lvgl.h>
#include <math.h>
#include <time.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "appConfig.h"
#include "dashboardUi.h"
#include "displayDriver.h"
#include "sensorReader.h"
#include "WiFiManagerExt.h"

const char* PROG_VERSION = "v1.0.3";

//--- Global objects
static DashboardUi dashboardUi;
static DisplayDriver displayDriver;
static SensorReader sensorReader;
static WiFiManagerExt wifiManagerExt;
static SensorData sensorData = {};
static bool sensorOnline = false;
static bool mqttEnabled = false;
static bool wifiReady = false;
static bool tilesVisible = false;
static uint32_t sensorStartMs = 0;
static uint32_t lastSensorReadMs = 0;
static uint32_t lastSensorRetryMs = 0;
static uint32_t lastMqttConnectTryMs = 0;
static uint32_t lastMqttPublishMs = 0;
static uint32_t lastTimeSyncTryMs = 0;
static uint32_t mqttStatusFlashUntilMs = 0;
static constexpr uint32_t kSensorRetryIntervalMs = 5000;
static constexpr uint32_t kMqttRetryIntervalMs = 5000;
static constexpr uint32_t kTimeSyncRetryMs = 60000;
static constexpr uint32_t kMqttStatusFlashMs = 800;
static bool timeSynced = false;

static WiFiClient mqttClientPlain;
static WiFiClientSecure mqttClientSecure;
static PubSubClient mqttClient(mqttClientPlain);

//--- Try to synchronize ESP32 clock over NTP while WiFi is connected
static bool syncTimeFromNtp()
{
  configTzTime("CET-1CEST,M3.5.0/2,M10.5.0/3", "pool.ntp.org", "time.nist.gov", "time.google.com");

  const uint32_t startedMs = millis();
  while ((millis() - startedMs) < 10000)
  {
    if (time(nullptr) > 1700000000)
    {
      timeSynced = true;
      Serial.println("NTP time synchronized");
      return true;
    }

    displayDriver.loop();
    wifiManagerExt.loop();
    delay(50);
  }

  timeSynced = false;
  Serial.println("Warning: NTP time sync failed");
  return false;
}

//--- Ensure time sync is retried periodically until successful
static void ensureTimeSync(uint32_t now)
{
  if (!wifiManagerExt.isWifiConnected() || timeSynced)
  {
    return;
  }

  if ((now - lastTimeSyncTryMs) < kTimeSyncRetryMs)
  {
    return;
  }

  lastTimeSyncTryMs = now;
  syncTimeFromNtp();
}

//--- Format current local time as ISO8601 (Europe/Amsterdam, with numeric offset)
static bool makeIsoTimestamp(char* out, size_t outSize)
{
  const time_t now = time(nullptr);
  if (now <= 0)
  {
    return false;
  }

  struct tm localTm;
  localtime_r(&now, &localTm);
  return strftime(out, outSize, "%Y-%m-%dT%H:%M:%S%z", &localTm) > 0;
}

//--- Show MQTT text briefly in the top-right status label on successful publish
static void updateMqttStatusFlash(uint32_t now)
{
  if (mqttStatusFlashUntilMs == 0)
  {
    return;
  }

  if (now < mqttStatusFlashUntilMs)
  {
    return;
  }

  mqttStatusFlashUntilMs = 0;
  dashboardUi.setMqttIndicator(false);
}

//--- Update the dashboard when WiFi manager opens the captive portal
static void onPortalStatus(const char* statusText, const char* detailText)
{
  const bool portalActive = (statusText != nullptr) && (strstr(statusText, "portal") != nullptr);
  const char* line2 = portalActive ? "Open 192.168.4.1 for portal" : "";
  dashboardUi.showFullScreenMessage(statusText, detailText, line2);
  displayDriver.loop();
  delay(20);
}

//--- Keep LVGL active while a full-screen status message should remain visible
static void showTransientStatusScreen(const char* titleText, const char* line1Text, const char* line2Text, uint32_t holdMs)
{
  dashboardUi.showFullScreenMessage(titleText, line1Text, line2Text);
  const uint32_t startMs = millis();
  while ((millis() - startMs) < holdMs)
  {
    displayDriver.loop();
    wifiManagerExt.loop();
    delay(5);
  }
}

//--- Create a stable MQTT client id from the chip MAC
static String buildMqttClientId()
{
  uint8_t mac[6] = {0};
  WiFi.macAddress(mac);

  char clientId[32];
  snprintf(
      clientId,
      sizeof(clientId),
      "deskAerosol-%02x%02x%02x",
      static_cast<unsigned int>(mac[3]),
      static_cast<unsigned int>(mac[4]),
      static_cast<unsigned int>(mac[5]));
  return String(clientId);
}

//--- Configure the MQTT transport and endpoint based on stored portal settings
static void configureMqttEndpoint()
{
  const MqttRuntimeConfig& cfg = wifiManagerExt.mqttConfig();
  const bool useTls = (cfg.brokerPort == 8883);

  if (useTls)
  {
    mqttClientSecure.setInsecure();
    mqttClient.setClient(mqttClientSecure);
  }
  else
  {
    mqttClient.setClient(mqttClientPlain);
  }

  mqttClient.setServer(cfg.brokerUrl.c_str(), cfg.brokerPort);
}

//--- Keep the MQTT connection alive with periodic reconnect attempts
static void maintainMqttConnection(uint32_t now)
{
  if (!mqttEnabled)
  {
    return;
  }

  if (!wifiManagerExt.isWifiConnected())
  {
    return;
  }

  if (mqttClient.connected())
  {
    return;
  }

  if ((now - lastMqttConnectTryMs) < kMqttRetryIntervalMs)
  {
    return;
  }

  lastMqttConnectTryMs = now;
  const MqttRuntimeConfig& cfg = wifiManagerExt.mqttConfig();
  const String clientId = buildMqttClientId();

  bool connected = false;
  if (cfg.username.length() == 0)
  {
    connected = mqttClient.connect(clientId.c_str());
  }
  else
  {
    connected = mqttClient.connect(clientId.c_str(), cfg.username.c_str(), cfg.password.c_str());
  }

  if (connected)
  {
    Serial.println("MQTT connected");
    return;
  }

  Serial.printf("MQTT connect failed (state=%d)\n", mqttClient.state());
}

//--- Publish one sensor sample in JSON format to the configured MQTT topic
static void publishMqttSampleIfDue(const SensorData& data, uint32_t now)
{
  if (!mqttEnabled || !data.valid)
  {
    return;
  }

  const MqttRuntimeConfig& cfg = wifiManagerExt.mqttConfig();
  if ((now - lastMqttPublishMs) < cfg.publishIntervalMs)
  {
    return;
  }

  if (!mqttClient.connected())
  {
    return;
  }

  if (!timeSynced)
  {
    ensureTimeSync(now);
    if (!timeSynced)
    {
      return;
    }
  }

  char timeStamp[32];
  if (!makeIsoTimestamp(timeStamp, sizeof(timeStamp)))
  {
    return;
  }

  char payload[320];
  snprintf(
      payload,
      sizeof(payload),
      "{\"pm1_0\":%.1f,\"pm2_5\":%.1f,\"pm4_0\":%.1f,\"pm10\":%.1f,\"humidity\":%.1f,\"temperature\":%.1f,\"voc\":%.0f,\"nox\":%.0f,\"co2\":%u,\"timeStamp\":\"%s\"}",
      data.pm1p0,
      data.pm2p5,
      data.pm4p0,
      data.pm10p0,
      data.humidity,
      data.temperature,
      data.vocIndex,
      data.noxIndex,
      static_cast<unsigned int>(data.co2),
      timeStamp);

  if (mqttClient.publish(cfg.topic.c_str(), payload))
  {
    lastMqttPublishMs = now;
    mqttStatusFlashUntilMs = now + kMqttStatusFlashMs;
    dashboardUi.setMqttIndicator(true);
  }
}

//--- Initialize WiFi (saved AP or portal) and prepare MQTT connectivity
static bool initConnectivity()
{
  wifiManagerExt.setPortalStatusCallback(onPortalStatus);
  dashboardUi.showFullScreenMessage("WiFi setup", "Trying saved credentials...", "");
  displayDriver.loop();

  if (!wifiManagerExt.beginAndConnect())
  {
    dashboardUi.showFullScreenMessage("WiFi failed", "No credentials or no AP connection", "Portal timeout after 5 minutes");
    mqttEnabled = false;
    return false;
  }

  const String hostName = wifiManagerExt.portalSsidString();
  const String ipOnly = wifiManagerExt.localIpString();

  char line2[128];
  snprintf(line2, sizeof(line2), "IP: %s\nNTP: synchronizing...", ipOnly.c_str());
  dashboardUi.showFullScreenMessage("WiFi connected", hostName.c_str(), line2);
  displayDriver.loop();

  syncTimeFromNtp();

  char ntpText[32];
  if (makeIsoTimestamp(ntpText, sizeof(ntpText)))
  {
    snprintf(line2, sizeof(line2), "IP: %s\nNTP: %s", ipOnly.c_str(), ntpText);
  }
  else
  {
    snprintf(line2, sizeof(line2), "IP: %s\nNTP: unavailable", ipOnly.c_str());
  }
  showTransientStatusScreen("WiFi connected", hostName.c_str(), line2, 2500);

  const MqttRuntimeConfig& cfg = wifiManagerExt.mqttConfig();
  const bool mqttConfigValid = (cfg.brokerUrl.length() > 0) && (cfg.topic.length() > 0);

  if (!mqttConfigValid)
  {
    dashboardUi.showFullScreenMessage("WiFi only mode", "MQTT is not configured", "Sensor dashboard will continue");
    displayDriver.loop();
    mqttEnabled = false;
    return true;
  }

  configureMqttEndpoint();
  mqttEnabled = true;
  return true;
}

//--- Generate a 0..1 triangle wave from a monotonically increasing phase
static float triangle01(float phase)
{
  float wrapped = phase - floorf(phase);
  if (wrapped < 0.5f)
  {
    return wrapped * 2.0f;
  }
  return (1.0f - wrapped) * 2.0f;

} //   triangle01()

//--- Advance simulated sensor values and push them to the dashboard
static void updateSimulationUi()
{
  static uint32_t lastUpdateMs = 0;
  static uint32_t updateCounter = 0;
  const uint32_t now = millis();

  if ((now - lastUpdateMs) < kSensorUpdateIntervalMs)
  {
    return;
  }

  lastUpdateMs = now;
  ++updateCounter;

  const float t = static_cast<float>(updateCounter);

  // Different periods and phase offsets keep tiles from peaking at the same time.
  const float pm1Norm = triangle01(t / 31.0f + 0.10f);
  const float pm25Norm = triangle01(t / 37.0f + 0.24f);
  const float pm4Norm = triangle01(t / 43.0f + 0.38f);
  const float pm10Norm = triangle01(t / 47.0f + 0.55f);
  const float tempNorm = triangle01(t / 53.0f + 0.08f);
  const float humNorm = triangle01(t / 41.0f + 0.67f);
  const float co2Norm = triangle01(t / 59.0f + 0.32f);
  const float vocNorm = triangle01(t / 29.0f + 0.79f);
  const float noxNorm = triangle01(t / 35.0f + 0.46f);

  auto remap = [](float v, float minValue, float maxValue) -> float
  {
    return minValue + v * (maxValue - minValue);
  };

  SensorData sim = {};
  sim.pm1p0 = remap(pm1Norm, 2.0f, 95.0f);
  sim.pm2p5 = remap(pm25Norm, 4.0f, 130.0f);
  sim.pm4p0 = remap(pm4Norm, 5.0f, 160.0f);
  sim.pm10p0 = remap(pm10Norm, 8.0f, 220.0f);
  sim.temperature = remap(tempNorm, 18.5f, 33.5f);
  sim.humidity = remap(humNorm, 32.0f, 92.0f);
  sim.co2 = static_cast<uint16_t>(remap(co2Norm, 420.0f, 2200.0f));
  sim.vocIndex = remap(vocNorm, 35.0f, 360.0f);
  sim.noxIndex = remap(noxNorm, 30.0f, 330.0f);
  sim.valid = true;
  sim.sampleAgeMs = 0;

  dashboardUi.setStatusText("SIMULATION");
  dashboardUi.showSensorData(sim);

  char updateText[64];
  snprintf(updateText, sizeof(updateText), "SIM update #%lu", static_cast<unsigned long>(updateCounter));
  dashboardUi.setLastUpdateText(updateText);

  if ((updateCounter % 4) == 0)
  {
    Serial.printf(
        "[STEP 9] SIM #%lu CO2=%u PM2.5=%.1f PM10=%.1f T=%.1f RH=%.1f VOC=%.0f NOx=%.0f\n",
        static_cast<unsigned long>(updateCounter),
        static_cast<unsigned int>(sim.co2),
        sim.pm2p5,
        sim.pm10p0,
        sim.temperature,
        sim.humidity,
        sim.vocIndex,
        sim.noxIndex);
  }

} //   updateSimulationUi()

//--- Print a numbered boot-step message to the serial console
static void logStep(uint8_t step, const char* text)
{
  Serial.printf("[STEP %u] %s\n", static_cast<unsigned int>(step), text);
}

//--- Format and display the last-update text
static void updateLastUpdateText(uint32_t ageMs)
{
  (void)ageMs;
  char buffer[64];
  const time_t now = time(nullptr);
  if (now > 0)
  {
    struct tm localTm;
    localtime_r(&now, &localTm);
    if (strftime(buffer, sizeof(buffer), "%H:%M:%S", &localTm) == 0)
    {
      snprintf(buffer, sizeof(buffer), "Time unavailable");
    }
  }
  else
  {
    snprintf(buffer, sizeof(buffer), "Time not synced");
  }
  dashboardUi.setLastUpdateText(buffer);

} //   updateLastUpdateText()

//--- Show sensor-offline status and periodic reconnect information
static void updateSensorOfflineStatus(uint32_t now)
{
  const uint32_t elapsedSinceRetry = now - lastSensorRetryMs;
  uint32_t retryInMs = 0;

  if (elapsedSinceRetry < kSensorRetryIntervalMs)
  {
    retryInMs = kSensorRetryIntervalMs - elapsedSinceRetry;
  }

  const uint32_t retryInSeconds = (retryInMs + 999) / 1000;
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "Sensor offline, retry in %lu s", static_cast<unsigned long>(retryInSeconds));
  dashboardUi.showSensorError("No SEN66 connected");
  dashboardUi.setLastUpdateText(buffer);

} //   updateSensorOfflineStatus()

//--- Print one full line with all measured values for debugging
static void logSensorData(const SensorData& data)
{
  Serial.printf(
      "PM1=%.1f PM2.5=%.1f PM4=%.1f PM10=%.1f RH=%.1f T=%.1f VOC=%.0f NOx=%.0f CO2=%u\n",
      data.pm1p0,
      data.pm2p5,
      data.pm4p0,
      data.pm10p0,
      data.humidity,
      data.temperature,
      data.vocIndex,
      data.noxIndex,
      static_cast<unsigned int>(data.co2));

} //   logSensorData()

//--- Perform one timed sensor update and refresh the dashboard
static void updateSensorAndUi()
{
  const uint32_t now = millis();
  enum class RuntimePhase : uint8_t
  {
    Offline = 0,
    Warmup = 1,
    WaitingNext = 2,
    Reading = 3
  };
  static RuntimePhase lastPhase = RuntimePhase::Reading;

  auto setPhase = [&](RuntimePhase phase, const char* text)
  {
    if (phase != lastPhase)
    {
      lastPhase = phase;
      Serial.printf("[STEP 9] %s\n", text);
    }
  };

  if (!sensorOnline)
  {
    setPhase(RuntimePhase::Offline, "Sensor offline / retrying");
    updateSensorOfflineStatus(now);

    if ((now - lastSensorRetryMs) < kSensorRetryIntervalMs)
    {
      return;
    }

    lastSensorRetryMs = now;
    sensorOnline = sensorReader.begin();

    if (!sensorOnline)
    {
      return;
    }

    sensorStartMs = now;
    lastSensorReadMs = now;
    tilesVisible = false;
    const String ipLine = String("IP: ") + wifiManagerExt.localIpString();

    char ntpText[32];
    const bool hasNtp = makeIsoTimestamp(ntpText, sizeof(ntpText));
    char ntpLine[48];
    if (hasNtp)
    {
      snprintf(ntpLine, sizeof(ntpLine), "NTP: %s", ntpText);
    }
    else
    {
      snprintf(ntpLine, sizeof(ntpLine), "NTP: synchronizing...");
    }

    char line2[96];
    snprintf(
        line2,
        sizeof(line2),
        "%s\n30 s remaining",
        ntpLine);

    dashboardUi.showFullScreenMessage("Warming up SEN66", ipLine.c_str(), line2);
    Serial.println("SEN66 connected after retry");
    return;
  }

  if ((now - sensorStartMs) < kSensorWarmupMs)
  {
    setPhase(RuntimePhase::Warmup, "Sensor warmup");
    const uint32_t elapsedMs = now - sensorStartMs;
    const uint32_t remainingMs = (elapsedMs < kSensorWarmupMs) ? (kSensorWarmupMs - elapsedMs) : 0;
    const uint32_t remainingSec = (remainingMs + 999) / 1000;

    const String ipLine = String("IP: ") + wifiManagerExt.localIpString();
    char ntpText[32];
    const bool hasNtp = makeIsoTimestamp(ntpText, sizeof(ntpText));
    char ntpLine[48];
    if (hasNtp)
    {
      snprintf(ntpLine, sizeof(ntpLine), "NTP: %s", ntpText);
    }
    else
    {
      snprintf(ntpLine, sizeof(ntpLine), "NTP: synchronizing...");
    }

    char line2[96];
    snprintf(
        line2,
        sizeof(line2),
        "%s\n%lu s remaining",
        ntpLine,
        static_cast<unsigned long>(remainingSec));
    dashboardUi.showFullScreenMessage("Warming up SEN66", ipLine.c_str(), line2);
    return;
  }

  if (!tilesVisible)
  {
    tilesVisible = true;
    dashboardUi.showBooting();
  }

  if ((now - lastSensorReadMs) < kSensorUpdateIntervalMs)
  {
    setPhase(RuntimePhase::WaitingNext, "Waiting for next sensor sample");
    updateLastUpdateText(now - lastSensorReadMs);
    return;
  }

  setPhase(RuntimePhase::Reading, "Reading sensor sample");
  lastSensorReadMs = now;
  sensorData.sampleAgeMs = 0;

  if (!sensorReader.read(sensorData))
  {
    dashboardUi.showSensorError("I2C read failed");
    return;
  }

  logSensorData(sensorData);
  dashboardUi.showSensorData(sensorData);
  updateLastUpdateText(0);
  publishMqttSampleIfDue(sensorData, now);

} //   updateSensorAndUi()

//--- Initialize display and build the dashboard screen
static bool initDisplayAndUi()
{
  logStep(1, "Initialize display driver");

  if (!displayDriver.begin())
  {
    Serial.println("Error: Display initialization failed");
    return false;
  }

  logStep(2, "Display init OK");

#if !defined(TEST_DISPLAY)
  logStep(3, "Build Dashboard UI objects");
  dashboardUi.begin();
  logStep(4, "Dashboard UI ready");
#endif
  return true;

} //   initDisplayAndUi()

//--- Initialize the external SEN66 sensor on the custom I2C bus
static void initSensor()
{
  sensorStartMs = millis();
  lastSensorRetryMs = sensorStartMs;
  sensorOnline = sensorReader.begin();

  if (!sensorOnline)
  {
    Serial.println("Warning: SEN66 not detected, dashboard continues without sensor");
  }

} //   initSensor()

//--- Arduino setup entry point
void setup()
{
  Serial.begin(115200);
  delay(200);
  randomSeed(static_cast<uint32_t>(micros()));

  Serial.println();
  Serial.println("Starting SEN66 dashboard for CYD");
#if defined(CYD_VARIANT_ST7789)
  Serial.println("Display variant: ST7789");
#else
  Serial.println("Display variant: ILI9341");
#endif
  Serial.printf("I2C SDA=%u SCL=%u\n", kI2cSdaPin, kI2cSclPin);
  logStep(0, "Boot sequence start");

  if (!initDisplayAndUi())
  {
    while (true)
    {
      delay(1000);
    }
  }

#if defined(TEST_DISPLAY)
  logStep(5, "Mode TEST_DISPLAY");
  Serial.println("TEST_DISPLAY enabled");
  Serial.println("Display diagnostic pattern is running");
  return;
#endif

#if defined(SIMULATION)
  logStep(5, "Mode SIMULATION");
  Serial.println("Sensor read disabled, synthetic values enabled");
  dashboardUi.showBooting();
  logStep(6, "Dashboard boot screen rendered");
  logStep(7, "Start SIMULATION update loop");
  return;
#endif

  logStep(5, "Mode FULL_RUNTIME");
  dashboardUi.showFullScreenMessage("Starting", "Preparing connectivity...", "");
  logStep(6, "WiFi status screen rendered");
  logStep(7, "Initialize WiFi + MQTT");
  wifiReady = initConnectivity();

  if (!wifiReady)
  {
    logStep(8, "WiFi not connected, waiting on status screen");
    return;
  }

  const String ipLine = String("IP: ") + wifiManagerExt.localIpString();
  char ntpText[32];
  const bool hasNtp = makeIsoTimestamp(ntpText, sizeof(ntpText));
  char ntpLine[48];
  if (hasNtp)
  {
    snprintf(ntpLine, sizeof(ntpLine), "NTP: %s", ntpText);
  }
  else
  {
    snprintf(ntpLine, sizeof(ntpLine), "NTP: synchronizing...");
  }

  char warmupLine2[96];
  snprintf(
      warmupLine2,
      sizeof(warmupLine2),
      "%s\n30 s remaining",
      ntpLine);
  dashboardUi.showFullScreenMessage("Warming up SEN66", ipLine.c_str(), warmupLine2);
  logStep(8, "Warmup screen rendered");
  logStep(9, "Initialize sensor");
  initSensor();
  logStep(10, "Sensor init completed");

} //   setup()

//--- Arduino main loop entry point
void loop()
{
#if defined(TEST_DISPLAY)
  displayDriver.runTestPattern();
  delay(5);
  return;
#endif

#if defined(SIMULATION)
  displayDriver.loop();
  wifiManagerExt.loop();
  updateSimulationUi();
  delay(5);
  return;
#endif

  if (!wifiReady)
  {
    displayDriver.loop();
    wifiManagerExt.loop();
    delay(5);
    return;
  }

  displayDriver.loop();
  wifiManagerExt.loop();
  ensureTimeSync(millis());
  maintainMqttConnection(millis());
  mqttClient.loop();
  updateSensorAndUi();
  updateMqttStatusFlash(millis());
  delay(5);

} //   loop()
