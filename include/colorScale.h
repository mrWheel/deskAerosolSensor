/*** Last Changed: 2026-03-29 - 13:32 ***/
#pragma once

#include <Arduino.h>
#include <lvgl.h>

float clamp01(float value);
float mapRangeClamped(float value, float inMin, float inMax);
float computePmBadness(float value);
float computePm10Badness(float value);
float computeCo2Badness(float value);
float computeVocBadness(float value);
float computeNoxBadness(float value);
float computeTemperatureBadness(float value);
float computeHumidityBadness(float value);
lv_color_t badnessToColor(float badness);
