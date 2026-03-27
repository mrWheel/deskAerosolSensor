#pragma once

#include <Arduino.h>

struct SensorData
{
  float pm1p0;
  float pm2p5;
  float pm4p0;
  float pm10p0;
  float humidity;
  float temperature;
  float vocIndex;
  float noxIndex;
  uint16_t co2;
  bool valid;
  uint32_t sampleAgeMs;
};
