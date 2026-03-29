/*** Last Changed: 2026-03-29 - 13:32 ***/
#pragma once

#include <Arduino.h>

struct MqttRuntimeConfig
{
  String brokerUrl;
  uint16_t brokerPort = 1883;
  String username;
  String password;
  String topic;
  uint32_t publishIntervalMs = 5000;
};

class WiFiManagerExt
{
public:
  using PortalStatusCallback = void (*)(const char* statusText, const char* detailText);

  WiFiManagerExt();

  bool beginAndConnect();
  void loop();
  void handleResetButton();

  bool isWifiConnected() const;
  const MqttRuntimeConfig& mqttConfig() const;
  String portalSsidString() const;
  String localIpString() const;

  void setPortalStatusCallback(PortalStatusCallback callback);

private:
  void loadMqttConfig();
  void saveMqttConfig();
  String buildPortalSsid() const;

  void fillPortalBuffers();
  void readPortalBuffers();

  static void onConfigPortalStarted();
  static void onSaveParams();

  static WiFiManagerExt* self;

  MqttRuntimeConfig config;
  PortalStatusCallback portalStatusCallback = nullptr;

  bool shouldSaveConfig = false;
  bool resetTriggered = false;
  uint32_t resetPressedSinceMs = 0;

  String portalSsid;

  char brokerBuf[80] = {};
  char userBuf[64] = {};
  char passBuf[64] = {};
  char portBuf[8] = {};
  char topicBuf[128] = {};
  char intervalBuf[16] = {};
};
