#pragma once

#include <Arduino.h>
#include <SensirionI2cSen66.h>
#include "sensorData.h"

class SensorReader
{
public:
  bool begin();
  bool read(SensorData& data);

private:
  SensirionI2cSen66 sen66;
};
