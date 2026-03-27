#include "sensorReader.h"
#include <Wire.h>
#include "appConfig.h"

//--- Initialize the SEN66 sensor and start continuous measurements
bool SensorReader::begin()
{
  Wire.begin(kI2cSdaPin, kI2cSclPin, 100000);

  sen66.begin(Wire, kSen66I2cAddress);

  const int16_t error = sen66.startContinuousMeasurement();

  if (error != 0)
  {
    char errorMessage[256];
    errorToString(error, errorMessage, sizeof(errorMessage));
    Serial.printf("Error: SEN66 startContinuousMeasurement failed: %s\n", errorMessage);
    return false;
  }

  Serial.println("SEN66 continuous measurement started");
  return true;

}   //   begin()

//--- Read all available measured values from the SEN66
bool SensorReader::read(SensorData& data)
{
  int16_t error = sen66.readMeasuredValues(
    data.pm1p0,
    data.pm2p5,
    data.pm4p0,
    data.pm10p0,
    data.humidity,
    data.temperature,
    data.vocIndex,
    data.noxIndex,
    data.co2
  );

  if (error != 0)
  {
    char errorMessage[256];
    errorToString(error, errorMessage, sizeof(errorMessage));
    Serial.printf("Warning: SEN66 read failed: %s\n", errorMessage);
    data.valid = false;
    return false;
  }

  data.valid = true;
  return true;

}   //   read()
