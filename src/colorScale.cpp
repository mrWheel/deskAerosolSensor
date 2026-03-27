#include "colorScale.h"

//--- Clamp floating point value to the range 0.0 .. 1.0
float clamp01(float value)
{
  if (value < 0.0f)
  {
    return 0.0f;
  }

  if (value > 1.0f)
  {
    return 1.0f;
  }

  return value;

}   //   clamp01()

//--- Map a value from an input range to 0.0 .. 1.0 and clamp it
float mapRangeClamped(float value, float inMin, float inMax)
{
  if (inMax <= inMin)
  {
    return 0.0f;
  }

  return clamp01((value - inMin) / (inMax - inMin));

}   //   mapRangeClamped()

//--- Approximate badness for PM1.0 / PM2.5 / PM4.0
float computePmBadness(float value)
{
  return mapRangeClamped(value, 0.0f, 55.4f);

}   //   computePmBadness()

//--- Approximate badness for PM10
float computePm10Badness(float value)
{
  return mapRangeClamped(value, 0.0f, 154.0f);

}   //   computePm10Badness()

//--- Approximate indoor ventilation badness for CO2
float computeCo2Badness(float value)
{
  return mapRangeClamped(value, 600.0f, 2000.0f);

}   //   computeCo2Badness()

//--- Approximate relative badness for the Sensirion VOC index
float computeVocBadness(float value)
{
  return mapRangeClamped(value, 100.0f, 400.0f);

}   //   computeVocBadness()

//--- Approximate relative badness for the Sensirion NOx index
float computeNoxBadness(float value)
{
  return mapRangeClamped(value, 1.0f, 300.0f);

}   //   computeNoxBadness()

//--- Approximate comfort badness for indoor temperature
float computeTemperatureBadness(float value)
{
  if (value < 21.0f)
  {
    return mapRangeClamped(21.0f - value, 0.0f, 6.0f);
  }

  if (value > 24.0f)
  {
    return mapRangeClamped(value - 24.0f, 0.0f, 8.0f);
  }

  return 0.0f;

}   //   computeTemperatureBadness()

//--- Approximate comfort badness for indoor humidity
float computeHumidityBadness(float value)
{
  if (value < 40.0f)
  {
    return mapRangeClamped(40.0f - value, 0.0f, 20.0f);
  }

  if (value > 60.0f)
  {
    return mapRangeClamped(value - 60.0f, 0.0f, 25.0f);
  }

  return 0.0f;

}   //   computeHumidityBadness()

//--- Convert a badness score to a blue -> red color gradient
lv_color_t badnessToColor(float badness)
{
  badness = clamp01(badness);

  const uint8_t red = static_cast<uint8_t>(60.0f + (195.0f * badness));
  const uint8_t green = static_cast<uint8_t>(180.0f - (140.0f * badness));
  const uint8_t blue = static_cast<uint8_t>(255.0f - (225.0f * badness));

  return lv_color_make(red, green, blue);

}   //   badnessToColor()
