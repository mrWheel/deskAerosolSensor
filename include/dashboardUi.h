/*** Last Changed: 2026-03-29 - 13:32 ***/
#pragma once

#include <Arduino.h>
#include <lvgl.h>
#include "sensorData.h"

class DashboardUi
{
public:
  void begin();
  void showBooting();
  void showFullScreenMessage(const char* titleText, const char* line1Text, const char* line2Text = "");
  void hideFullScreenMessage();
  void showSensorData(const SensorData& data);
  void showReadError(const char* errorText);
  void showSensorError(const char* errorText);
  void setStatusText(const char* statusText);
  void setMqttIndicator(bool visible);
  void setLastUpdateText(const char* updateText);

private:
  struct Tile
  {
    lv_obj_t* card;
    lv_obj_t* titleLabel;
    lv_obj_t* valueLabel;
    lv_obj_t* unitLabel;
  };

  lv_obj_t* screen = nullptr;
  lv_obj_t* header = nullptr;
  lv_obj_t* titleLabel = nullptr;
  lv_obj_t* statusTopRow = nullptr;
  lv_obj_t* statusLabel = nullptr;
  lv_obj_t* mqttLabel = nullptr;
  lv_obj_t* lastUpdateLabel = nullptr;
  lv_obj_t* grid = nullptr;
  lv_obj_t* fullScreenLayer = nullptr;
  lv_obj_t* fullScreenTitle = nullptr;
  lv_obj_t* fullScreenLine1 = nullptr;
  lv_obj_t* fullScreenLine2 = nullptr;

  Tile tilePm1;
  Tile tilePm25;
  Tile tilePm4;
  Tile tilePm10;
  Tile tileTemp;
  Tile tileRh;
  Tile tileCo2;
  Tile tileVoc;
  Tile tileNox;

  void createHeader();
  void createGrid();
  void createTile(
      Tile& tile,
      const char* titleText,
      uint8_t col,
      uint8_t row);
  void setTileValue(
      Tile& tile,
      const char* valueText,
      const char* unitText,
      float badness);
  void setTilePlaceholder(Tile& tile, const char* text, const char* unitText);
};
