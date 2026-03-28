#include "WiFiManagerExt.h"

#include <WiFi.h>
#include <Preferences.h>
#include <WiFiManager.h>

WiFiManagerExt* WiFiManagerExt::self = nullptr;

namespace
{
  constexpr const char* kNamespace = "mqttcfg";
  constexpr uint32_t kPortalTimeoutSeconds = 300;
  constexpr uint32_t kResetHoldMs = 10000;
}

WiFiManagerExt::WiFiManagerExt()
{
  self = this;
}

bool WiFiManagerExt::beginAndConnect()
{
  pinMode(0, INPUT_PULLUP);

  loadMqttConfig();
  fillPortalBuffers();
  portalSsid = buildPortalSsid();

  WiFiManager wifiManager;
  wifiManager.setConfigPortalBlocking(true);
  wifiManager.setConfigPortalTimeout(kPortalTimeoutSeconds);
  wifiManager.setSaveParamsCallback(onSaveParams);
  wifiManager.setAPCallback([](WiFiManager*)
  {
    onConfigPortalStarted();
  });

  WiFiManagerParameter mqttBrokerParam("mqtt_broker", "MQTT broker URL", brokerBuf, sizeof(brokerBuf));
  WiFiManagerParameter mqttUserParam("mqtt_user", "MQTT username", userBuf, sizeof(userBuf));
  WiFiManagerParameter mqttPassParam("mqtt_pass", "MQTT password", passBuf, sizeof(passBuf));
  WiFiManagerParameter mqttPortParam("mqtt_port", "MQTT broker port", portBuf, sizeof(portBuf));
  WiFiManagerParameter mqttTopicParam("mqtt_topic", "MQTT topic", topicBuf, sizeof(topicBuf));
  WiFiManagerParameter mqttIntervalParam("mqtt_interval", "MQTT publish interval (ms)", intervalBuf, sizeof(intervalBuf));

  wifiManager.addParameter(&mqttBrokerParam);
  wifiManager.addParameter(&mqttUserParam);
  wifiManager.addParameter(&mqttPassParam);
  wifiManager.addParameter(&mqttPortParam);
  wifiManager.addParameter(&mqttTopicParam);
  wifiManager.addParameter(&mqttIntervalParam);

  if (portalStatusCallback != nullptr)
  {
    portalStatusCallback("WiFi setup", "Trying saved credentials...");
  }

  shouldSaveConfig = false;
  const bool connected = wifiManager.autoConnect(portalSsid.c_str());

  if (!connected)
  {
    Serial.println("WiFi connection failed or portal timeout reached");
    if (portalStatusCallback != nullptr)
    {
      portalStatusCallback("WiFi failed", "Portal timeout (5 min)");
    }
    return false;
  }

  strncpy(brokerBuf, mqttBrokerParam.getValue(), sizeof(brokerBuf) - 1);
  strncpy(userBuf, mqttUserParam.getValue(), sizeof(userBuf) - 1);
  strncpy(passBuf, mqttPassParam.getValue(), sizeof(passBuf) - 1);
  strncpy(portBuf, mqttPortParam.getValue(), sizeof(portBuf) - 1);
  strncpy(topicBuf, mqttTopicParam.getValue(), sizeof(topicBuf) - 1);
  strncpy(intervalBuf, mqttIntervalParam.getValue(), sizeof(intervalBuf) - 1);

  readPortalBuffers();
  saveMqttConfig();

  Serial.print("WiFi connected. IP: ");
  Serial.println(WiFi.localIP());

  if (portalStatusCallback != nullptr)
  {
    portalStatusCallback("WiFi connected", localIpString().c_str());
  }

  return true;
}

void WiFiManagerExt::loop()
{
  handleResetButton();
}

void WiFiManagerExt::handleResetButton()
{
  if (resetTriggered)
  {
    return;
  }

  const bool pressed = (digitalRead(0) == LOW);
  const uint32_t now = millis();

  if (!pressed)
  {
    resetPressedSinceMs = 0;
    return;
  }

  if (resetPressedSinceMs == 0)
  {
    resetPressedSinceMs = now;
    return;
  }

  if ((now - resetPressedSinceMs) < kResetHoldMs)
  {
    return;
  }

  resetTriggered = true;
  Serial.println("GPIO0 held for 10s: clearing WiFi settings and restarting...");

  WiFiManager wifiManager;
  wifiManager.resetSettings();
  WiFi.disconnect(true, true);
  delay(250);
  ESP.restart();
}

bool WiFiManagerExt::isWifiConnected() const
{
  return WiFi.status() == WL_CONNECTED;
}

const MqttRuntimeConfig& WiFiManagerExt::mqttConfig() const
{
  return config;
}

String WiFiManagerExt::portalSsidString() const
{
  return portalSsid;
}

String WiFiManagerExt::localIpString() const
{
  return WiFi.localIP().toString();
}

void WiFiManagerExt::setPortalStatusCallback(PortalStatusCallback callback)
{
  portalStatusCallback = callback;
}

void WiFiManagerExt::loadMqttConfig()
{
  Preferences preferences;
  preferences.begin(kNamespace, true);

  config.brokerUrl = preferences.getString("broker", "");
  config.username = preferences.getString("user", "");
  config.password = preferences.getString("pass", "");
  config.brokerPort = static_cast<uint16_t>(preferences.getUInt("port", 1883));
  config.topic = preferences.getString("topic", "deskAerosolSensor/data");
  config.publishIntervalMs = preferences.getUInt("interval", 5000);

  preferences.end();
}

void WiFiManagerExt::saveMqttConfig()
{
  Preferences preferences;
  preferences.begin(kNamespace, false);

  preferences.putString("broker", config.brokerUrl);
  preferences.putString("user", config.username);
  preferences.putString("pass", config.password);
  preferences.putUInt("port", config.brokerPort);
  preferences.putString("topic", config.topic);
  preferences.putUInt("interval", config.publishIntervalMs);

  preferences.end();
}

String WiFiManagerExt::buildPortalSsid() const
{
  uint8_t mac[6] = {0};
  WiFi.macAddress(mac);

  char apName[32];
  snprintf(
    apName,
    sizeof(apName),
    "DAS-%02x-%02x-%02x",
    static_cast<unsigned int>(mac[3]),
    static_cast<unsigned int>(mac[4]),
    static_cast<unsigned int>(mac[5])
  );

  return String(apName);
}

void WiFiManagerExt::fillPortalBuffers()
{
  snprintf(brokerBuf, sizeof(brokerBuf), "%s", config.brokerUrl.c_str());
  snprintf(userBuf, sizeof(userBuf), "%s", config.username.c_str());
  snprintf(passBuf, sizeof(passBuf), "%s", config.password.c_str());
  snprintf(portBuf, sizeof(portBuf), "%u", static_cast<unsigned int>(config.brokerPort));
  snprintf(topicBuf, sizeof(topicBuf), "%s", config.topic.c_str());
  snprintf(intervalBuf, sizeof(intervalBuf), "%lu", static_cast<unsigned long>(config.publishIntervalMs));
}

void WiFiManagerExt::readPortalBuffers()
{
  config.brokerUrl = String(brokerBuf);
  config.username = String(userBuf);
  config.password = String(passBuf);
  config.topic = String(topicBuf);

  const long portValue = strtol(portBuf, nullptr, 10);
  if (portValue > 0 && portValue <= 65535)
  {
    config.brokerPort = static_cast<uint16_t>(portValue);
  }

  const long intervalValue = strtol(intervalBuf, nullptr, 10);
  if (intervalValue >= 500)
  {
    config.publishIntervalMs = static_cast<uint32_t>(intervalValue);
  }
}

void WiFiManagerExt::onConfigPortalStarted()
{
  if (self == nullptr)
  {
    return;
  }

  Serial.println("WiFi portal started");
  Serial.print("Connect to SSID: ");
  Serial.println(self->portalSsid);

  if (self->portalStatusCallback != nullptr)
  {
    String detail = String("Connect to ") + self->portalSsid;
    self->portalStatusCallback("WiFi portal started", detail.c_str());
  }
}

void WiFiManagerExt::onSaveParams()
{
  if (self == nullptr)
  {
    return;
  }

  self->shouldSaveConfig = true;
}
