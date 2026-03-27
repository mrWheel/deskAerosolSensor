#include <Arduino.h>
#include <Wire.h>
#include <lvgl.h>
#include <math.h>
#include "appConfig.h"
#include "dashboardUi.h"
#include "displayDriver.h"
#include "sensorReader.h"

const char* PROG_VERSION = "v0.1.0";

//--- Global objects
static DashboardUi dashboardUi;
static DisplayDriver displayDriver;
static SensorReader sensorReader;
static SensorData sensorData = {};
static bool sensorOnline = false;
static uint32_t sensorStartMs = 0;
static uint32_t lastSensorReadMs = 0;
static uint32_t lastSensorRetryMs = 0;
static constexpr uint32_t kSensorRetryIntervalMs = 5000;

//--- Generate a 0..1 triangle wave from a monotonically increasing phase
static float triangle01(float phase)
{
  float wrapped = phase - floorf(phase);
  if (wrapped < 0.5f)
  {
    return wrapped * 2.0f;
  }
  return (1.0f - wrapped) * 2.0f;

}   //   triangle01()

//--- Advance simulated sensor values and push them to the dashboard
static void updateSimulationUi()
{
  static uint32_t lastUpdateMs = 0;
  static uint32_t updateCounter = 0;
  const uint32_t now = millis();

  if ((now - lastUpdateMs) < 1000)
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
      sim.noxIndex
    );
  }

}   //   updateSimulationUi()

//--- Print a numbered boot-step message to the serial console
static void logStep(uint8_t step, const char* text)
{
  Serial.printf("[STEP %u] %s\n", static_cast<unsigned int>(step), text);
}

//--- Format and display the last-update text
static void updateLastUpdateText(uint32_t ageMs)
{
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "Last update %lu ms ago", static_cast<unsigned long>(ageMs));
  dashboardUi.setLastUpdateText(buffer);

}   //   updateLastUpdateText()

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
  dashboardUi.setStatusText("No SEN66 connected");
  dashboardUi.setLastUpdateText(buffer);

}   //   updateSensorOfflineStatus()

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
    static_cast<unsigned int>(data.co2)
  );

}   //   logSensorData()

//--- Perform one timed sensor update and refresh the dashboard
static void updateSensorAndUi()
{
  const uint32_t now = millis();
  enum class RuntimePhase : uint8_t { Offline = 0, Warmup = 1, WaitingNext = 2, Reading = 3 };
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
    dashboardUi.setStatusText("SEN66 connected");
    dashboardUi.setLastUpdateText("Warming up sensor");
    Serial.println("SEN66 connected after retry");
    return;
  }

  if ((now - sensorStartMs) < kSensorWarmupMs)
  {
    setPhase(RuntimePhase::Warmup, "Sensor warmup");
    dashboardUi.setStatusText("Warming up");
    updateLastUpdateText(now - sensorStartMs);
    return;
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
    dashboardUi.showReadError("Read retry");
    return;
  }

  logSensorData(sensorData);
  dashboardUi.showSensorData(sensorData);
  updateLastUpdateText(0);

}   //   updateSensorAndUi()

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

}   //   initDisplayAndUi()

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

}   //   initSensor()

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
  dashboardUi.showBooting();
  logStep(6, "Boot screen rendered");
  logStep(7, "Initialize sensor");
  initSensor();
  logStep(8, "Sensor init completed");

}   //   setup()

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
  updateSimulationUi();
  delay(5);
  return;
#endif

  displayDriver.loop();
  updateSensorAndUi();
  delay(5);

}   //   loop()
