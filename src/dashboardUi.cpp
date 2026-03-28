#include "dashboardUi.h"
#include "colorScale.h"

//--- Create the full dashboard on the active LVGL screen
void DashboardUi::begin()
{
  screen = lv_scr_act();

  lv_obj_set_style_bg_color(screen, lv_color_hex(0x0B1020), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);
  lv_obj_set_style_pad_all(screen, 0, 0);

  createHeader();
  createGrid();
  showBooting();

}   //   begin()

//--- Show a booting state before the first valid sample arrives
void DashboardUi::showBooting()
{
  hideFullScreenMessage();

  setStatusText("Starting sensor...");
  setLastUpdateText("Waiting for first sample");

  setTilePlaceholder(tilePm1, "--", "ug/m3");
  setTilePlaceholder(tilePm25, "--", "ug/m3");
  setTilePlaceholder(tilePm4, "--", "ug/m3");
  setTilePlaceholder(tilePm10, "--", "ug/m3");
  setTilePlaceholder(tileTemp, "--", "C");
  setTilePlaceholder(tileRh, "--", "%RH");
  setTilePlaceholder(tileCo2, "--", "ppm");
  setTilePlaceholder(tileVoc, "--", "index");
  setTilePlaceholder(tileNox, "--", "index");

}   //   showBooting()

//--- Show a full-screen status panel and hide the tile dashboard
void DashboardUi::showFullScreenMessage(const char* titleText, const char* line1Text, const char* line2Text)
{
  if (header != nullptr)
  {
    lv_obj_add_flag(header, LV_OBJ_FLAG_HIDDEN);
  }

  if (grid != nullptr)
  {
    lv_obj_add_flag(grid, LV_OBJ_FLAG_HIDDEN);
  }

  if (fullScreenLayer == nullptr)
  {
    fullScreenLayer = lv_obj_create(screen);
    lv_obj_set_size(fullScreenLayer, lv_pct(100), lv_pct(100));
    lv_obj_align(fullScreenLayer, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_radius(fullScreenLayer, 0, 0);
    lv_obj_set_style_border_width(fullScreenLayer, 0, 0);
    lv_obj_set_style_bg_color(fullScreenLayer, lv_color_hex(0x0B1020), 0);
    lv_obj_set_style_bg_opa(fullScreenLayer, LV_OPA_COVER, 0);
    lv_obj_set_style_pad_left(fullScreenLayer, 14, 0);
    lv_obj_set_style_pad_right(fullScreenLayer, 14, 0);
    lv_obj_set_style_pad_top(fullScreenLayer, 16, 0);
    lv_obj_set_style_pad_bottom(fullScreenLayer, 16, 0);
    lv_obj_set_layout(fullScreenLayer, LV_LAYOUT_FLEX);
    lv_obj_set_flex_flow(fullScreenLayer, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(fullScreenLayer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    fullScreenTitle = lv_label_create(fullScreenLayer);
    lv_obj_set_width(fullScreenTitle, lv_pct(100));
    lv_obj_set_style_text_align(fullScreenTitle, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(fullScreenTitle, &lv_font_montserrat_24, 0);
    lv_obj_set_style_text_color(fullScreenTitle, lv_color_hex(0xF8FAFC), 0);

    fullScreenLine1 = lv_label_create(fullScreenLayer);
    lv_obj_set_width(fullScreenLine1, lv_pct(100));
    lv_obj_set_style_text_align(fullScreenLine1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(fullScreenLine1, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_color(fullScreenLine1, lv_color_hex(0x93C5FD), 0);

    fullScreenLine2 = lv_label_create(fullScreenLayer);
    lv_obj_set_width(fullScreenLine2, lv_pct(100));
    lv_obj_set_style_text_align(fullScreenLine2, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_font(fullScreenLine2, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(fullScreenLine2, lv_color_hex(0x94A3B8), 0);
  }

  lv_obj_clear_flag(fullScreenLayer, LV_OBJ_FLAG_HIDDEN);
  lv_label_set_text(fullScreenTitle, titleText != nullptr ? titleText : "");
  lv_label_set_text(fullScreenLine1, line1Text != nullptr ? line1Text : "");
  lv_label_set_text(fullScreenLine2, line2Text != nullptr ? line2Text : "");
}

//--- Hide full-screen status panel and show normal dashboard layout
void DashboardUi::hideFullScreenMessage()
{
  if (fullScreenLayer != nullptr)
  {
    lv_obj_add_flag(fullScreenLayer, LV_OBJ_FLAG_HIDDEN);
  }

  if (header != nullptr)
  {
    lv_obj_clear_flag(header, LV_OBJ_FLAG_HIDDEN);
  }

  if (grid != nullptr)
  {
    lv_obj_clear_flag(grid, LV_OBJ_FLAG_HIDDEN);
  }
}

//--- Update all tiles with a fresh sensor sample
void DashboardUi::showSensorData(const SensorData& data)
{
  hideFullScreenMessage();
  setStatusText("Live");

  char buf[16];

  snprintf(buf, sizeof(buf), "%.1f", data.pm1p0);
  setTileValue(tilePm1, buf, "ug/m3", computePmBadness(data.pm1p0));

  snprintf(buf, sizeof(buf), "%.1f", data.pm2p5);
  setTileValue(tilePm25, buf, "ug/m3", computePmBadness(data.pm2p5));

  snprintf(buf, sizeof(buf), "%.1f", data.pm4p0);
  setTileValue(tilePm4, buf, "ug/m3", computePmBadness(data.pm4p0));

  snprintf(buf, sizeof(buf), "%.1f", data.pm10p0);
  setTileValue(tilePm10, buf, "ug/m3", computePm10Badness(data.pm10p0));

  snprintf(buf, sizeof(buf), "%.1f", data.temperature);
  setTileValue(tileTemp, buf, "C", computeTemperatureBadness(data.temperature));

  snprintf(buf, sizeof(buf), "%.1f", data.humidity);
  setTileValue(tileRh, buf, "%RH", computeHumidityBadness(data.humidity));

  snprintf(buf, sizeof(buf), "%u", static_cast<unsigned int>(data.co2));
  setTileValue(tileCo2, buf, "ppm", computeCo2Badness(data.co2));

  snprintf(buf, sizeof(buf), "%.0f", data.vocIndex);
  setTileValue(tileVoc, buf, "index", computeVocBadness(data.vocIndex));

  snprintf(buf, sizeof(buf), "%.0f", data.noxIndex);
  setTileValue(tileNox, buf, "index", computeNoxBadness(data.noxIndex));

}   //   showSensorData()

//--- Show a temporary read error without destroying the current values
void DashboardUi::showReadError(const char* errorText)
{
  setStatusText(errorText);

}   //   showReadError()

//--- Show a sensor communication error on all tiles
void DashboardUi::showSensorError(const char* errorText)
{
  hideFullScreenMessage();
  setStatusText(errorText);

  const float maxBadness = 1.0f;
  setTileValue(tilePm1,  "ERR", "", maxBadness);
  setTileValue(tilePm25, "ERR", "", maxBadness);
  setTileValue(tilePm4,  "ERR", "", maxBadness);
  setTileValue(tilePm10, "ERR", "", maxBadness);
  setTileValue(tileTemp, "ERR", "", maxBadness);
  setTileValue(tileRh,   "ERR", "", maxBadness);
  setTileValue(tileCo2,  "ERR", "", maxBadness);
  setTileValue(tileVoc,  "ERR", "", maxBadness);
  setTileValue(tileNox,  "ERR", "", maxBadness);

}   //   showSensorError()

//--- Update the small status label in the header
void DashboardUi::setStatusText(const char* statusText)
{
  if (statusLabel != nullptr)
  {
    lv_label_set_text(statusLabel, statusText);
  }

}   //   setStatusText()

//--- Update the last-update label in the header
void DashboardUi::setLastUpdateText(const char* updateText)
{
  if (lastUpdateLabel != nullptr)
  {
    lv_label_set_text(lastUpdateLabel, updateText);
  }

}   //   setLastUpdateText()

//--- Build the compact header bar
void DashboardUi::createHeader()
{
  header = lv_obj_create(screen);
  lv_obj_set_size(header, lv_pct(100), 42);
  lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_radius(header, 0, 0);
  lv_obj_set_style_border_width(header, 0, 0);
  lv_obj_set_style_bg_color(header, lv_color_hex(0x111827), 0);
  lv_obj_set_style_bg_opa(header, LV_OPA_COVER, 0);
  lv_obj_set_style_pad_left(header, 10, 0);
  lv_obj_set_style_pad_right(header, 10, 0);
  lv_obj_set_style_pad_top(header, 6, 0);
  lv_obj_set_style_pad_bottom(header, 6, 0);
  lv_obj_set_layout(header, 0);

  titleLabel = lv_label_create(header);
  lv_label_set_text(titleLabel, "Indoor Air");
  lv_obj_align(titleLabel, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_18, 0);
  lv_obj_set_style_text_color(titleLabel, lv_color_hex(0xE2E8F0), 0);

  lv_obj_t* rightGroup = lv_obj_create(header);
  lv_obj_set_size(rightGroup, 190, 30);
  lv_obj_align(rightGroup, LV_ALIGN_RIGHT_MID, -6, -2);
  lv_obj_set_style_bg_opa(rightGroup, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(rightGroup, 0, 0);
  lv_obj_set_style_pad_all(rightGroup, 0, 0);
  lv_obj_set_style_pad_row(rightGroup, 0, 0);
  lv_obj_set_layout(rightGroup, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(rightGroup, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(rightGroup, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

  statusLabel = lv_label_create(rightGroup);
  lv_label_set_text(statusLabel, "Booting");
  lv_obj_set_width(statusLabel, lv_pct(100));
  lv_obj_set_style_text_align(statusLabel, LV_TEXT_ALIGN_LEFT, 0);
  lv_obj_set_style_text_font(statusLabel, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_color(statusLabel, lv_color_hex(0x93C5FD), 0);

  lastUpdateLabel = lv_label_create(rightGroup);
  lv_label_set_text(lastUpdateLabel, "Waiting");
  lv_obj_set_width(lastUpdateLabel, lv_pct(100));
  lv_obj_set_style_text_align(lastUpdateLabel, LV_TEXT_ALIGN_LEFT, 0);
  lv_obj_set_style_text_font(lastUpdateLabel, &lv_font_montserrat_12, 0);
  lv_obj_set_style_text_color(lastUpdateLabel, lv_color_hex(0x94A3B8), 0);

}   //   createHeader()

//--- Build the 3 x 3 tile grid
void DashboardUi::createGrid()
{
  static lv_coord_t columnDescriptor[] =
  {
    LV_GRID_FR(1),
    LV_GRID_FR(1),
    LV_GRID_FR(1),
    LV_GRID_TEMPLATE_LAST
  };

  static lv_coord_t rowDescriptor[] =
  {
    LV_GRID_FR(1),
    LV_GRID_FR(1),
    LV_GRID_FR(1),
    LV_GRID_TEMPLATE_LAST
  };

  grid = lv_obj_create(screen);
  lv_obj_set_size(grid, lv_pct(100), 190);
  lv_obj_align(grid, LV_ALIGN_TOP_MID, 0, 48);
  lv_obj_set_style_radius(grid, 0, 0);
  lv_obj_set_style_border_width(grid, 0, 0);
  lv_obj_set_style_bg_opa(grid, LV_OPA_TRANSP, 0);
  lv_obj_set_style_pad_left(grid, 6, 0);
  lv_obj_set_style_pad_right(grid, 6, 0);
  lv_obj_set_style_pad_top(grid, 0, 0);
  lv_obj_set_style_pad_bottom(grid, 0, 0);
  lv_obj_set_style_pad_row(grid, 6, 0);
  lv_obj_set_style_pad_column(grid, 6, 0);
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_grid_dsc_array(grid, columnDescriptor, rowDescriptor);

  createTile(tileCo2, "CO2", 0, 0);
  createTile(tilePm25, "PM2.5", 1, 0);
  createTile(tileVoc, "VOC", 2, 0);

  createTile(tilePm1, "PM1.0", 0, 1);
  createTile(tilePm4, "PM4.0", 1, 1);
  createTile(tilePm10, "PM10", 2, 1);

  createTile(tileTemp, "Temp", 0, 2);
  createTile(tileRh, "Hum", 1, 2);
  createTile(tileNox, "NOx", 2, 2);

}   //   createGrid()

//--- Create one metric tile
void DashboardUi::createTile(
  Tile& tile,
  const char* titleText,
  uint8_t col,
  uint8_t row
)
{
  tile.card = lv_obj_create(grid);
  lv_obj_set_grid_cell(
    tile.card,
    LV_GRID_ALIGN_STRETCH, col, 1,
    LV_GRID_ALIGN_STRETCH, row, 1
  );
  lv_obj_set_style_radius(tile.card, 12, 0);
  lv_obj_set_style_border_width(tile.card, 1, 0);
  lv_obj_set_style_border_color(tile.card, lv_color_hex(0x334155), 0);
  lv_obj_set_style_bg_color(tile.card, lv_color_hex(0x111827), 0);
  lv_obj_set_style_bg_opa(tile.card, LV_OPA_COVER, 0);
  lv_obj_set_style_pad_left(tile.card, 8, 0);
  lv_obj_set_style_pad_right(tile.card, 8, 0);
  lv_obj_set_style_pad_top(tile.card, 6, 0);
  lv_obj_set_style_pad_bottom(tile.card, 6, 0);
  lv_obj_set_layout(tile.card, LV_LAYOUT_FLEX);
  lv_obj_set_flex_flow(tile.card, LV_FLEX_FLOW_COLUMN);
  lv_obj_set_flex_align(tile.card, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

  tile.titleLabel = lv_label_create(tile.card);
  lv_label_set_text(tile.titleLabel, titleText);
  lv_obj_set_style_text_font(tile.titleLabel, &lv_font_montserrat_14, 0);
  lv_obj_set_style_text_color(tile.titleLabel, lv_color_hex(0xE2E8F0), 0);

  tile.valueLabel = lv_label_create(tile.card);
  lv_label_set_text(tile.valueLabel, "--");
  lv_obj_set_style_text_font(tile.valueLabel, &lv_font_montserrat_24, 0);
  lv_obj_set_style_text_color(tile.valueLabel, lv_color_hex(0x60A5FA), 0);

  tile.unitLabel = lv_label_create(tile.card);
  lv_label_set_text(tile.unitLabel, "");
  lv_obj_set_style_text_font(tile.unitLabel, &lv_font_montserrat_12, 0);
  lv_obj_set_style_text_color(tile.unitLabel, lv_color_hex(0x94A3B8), 0);

}   //   createTile()

//--- Write a value, unit and color into a tile
void DashboardUi::setTileValue(
  Tile& tile,
  const char* valueText,
  const char* unitText,
  float badness
)
{
  const lv_color_t valueColor = badnessToColor(badness);
  lv_label_set_text(tile.valueLabel, valueText);
  lv_label_set_text(tile.unitLabel, unitText);
  lv_obj_set_style_text_color(tile.valueLabel, valueColor, 0);
  lv_obj_set_style_bg_color(tile.card, valueColor, LV_PART_SCROLLBAR);

}   //   setTileValue()

//--- Write a placeholder value into a tile
void DashboardUi::setTilePlaceholder(Tile& tile, const char* text, const char* unitText)
{
  const lv_color_t placeholderColor = lv_color_hex(0x60A5FA);
  lv_label_set_text(tile.valueLabel, text);
  lv_label_set_text(tile.unitLabel, unitText);
  lv_obj_set_style_text_color(tile.valueLabel, placeholderColor, 0);
  lv_obj_set_style_bg_color(tile.card, placeholderColor, LV_PART_SCROLLBAR);

}   //   setTilePlaceholder()
