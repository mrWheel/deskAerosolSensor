#include "displayDriver.h"
#include "appConfig.h"
#include <esp_timer.h>
#include <esp_heap_caps.h>

DisplayDriver::CydDisplay DisplayDriver::tft;
lv_disp_draw_buf_t DisplayDriver::drawBuffer;
lv_disp_drv_t DisplayDriver::displayDriver;
lv_color_t* DisplayDriver::frameBuffer = nullptr;
esp_timer_handle_t DisplayDriver::tickTimer = nullptr;

//--- Configure the CYD display controller, SPI bus and backlight
DisplayDriver::CydDisplay::CydDisplay()
{
  {
    auto config = bus.config();
    config.spi_host = VSPI_HOST;
    config.spi_mode = 0;
    config.freq_write = kDisplaySpiWriteHz;
    config.freq_read = kDisplaySpiReadHz;
    config.spi_3wire = false;
    config.use_lock = true;
    config.dma_channel = SPI_DMA_CH_AUTO;
    config.pin_sclk = 14;
    config.pin_mosi = 13;
    config.pin_miso = 12;
    config.pin_dc = 2;
    bus.config(config);
    panel.setBus(&bus);
  }

  {
    auto config = panel.config();
    config.pin_cs = 15;
    config.pin_rst = -1;
    config.pin_busy = -1;
    config.panel_width = kDisplayPanelWidth;
    config.panel_height = kDisplayPanelHeight;
    config.offset_x = kDisplayOffsetX;
    config.offset_y = kDisplayOffsetY;
    config.memory_width = kDisplayPanelWidth;
    config.memory_height = kDisplayPanelHeight;
    config.offset_rotation = 0;
    config.dummy_read_pixel = 8;
    config.dummy_read_bits = 1;
    config.readable = true;
    config.invert = kDisplayInvert;
    config.rgb_order = kDisplayRgbOrder;
    config.dlen_16bit = false;
    config.bus_shared = false;
    panel.config(config);
  }

  {
    auto config = light.config();
#if defined(CYD_VARIANT_ST7789)
    config.pin_bl = 27;
#else
    config.pin_bl = 21;
#endif
    config.invert = false;
    config.freq = 44100;
    config.pwm_channel = 7;
    light.config(config);
    panel.setLight(&light);
  }

  setPanel(&panel);

}   //   CydDisplay()

//--- LVGL flush callback that copies one area to the LCD
void DisplayDriver::flushDisplay(lv_disp_drv_t* displayDriver, const lv_area_t* area, lv_color_t* colorMap)
{
  const uint32_t width = static_cast<uint32_t>(area->x2 - area->x1 + 1);
  const uint32_t height = static_cast<uint32_t>(area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.pushImage(area->x1, area->y1, width, height, reinterpret_cast<lgfx::rgb565_t*>(colorMap));
  tft.endWrite();

  lv_disp_flush_ready(displayDriver);

}   //   flushDisplay()

//--- Periodic 1 ms LVGL tick source
void DisplayDriver::tickTask(void* arg)
{
  static_cast<void>(arg);
  lv_tick_inc(1);

}   //   tickTask()

//--- Initialize LCD, LVGL and the frame buffer
bool DisplayDriver::begin()
{
  tft.init();
  tft.setRotation(kDisplayRotation);
  tft.setBrightness(255);

  const uint16_t screenWidth = tft.width();
  const uint16_t screenHeight = tft.height();

#if defined(TEST_DISPLAY)
  tft.fillScreen(0x0000);
  return true;
#endif

  lv_init();

  frameBuffer = static_cast<lv_color_t*>(heap_caps_malloc(
    screenWidth * 20 * sizeof(lv_color_t),
    MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL
  ));

  if (frameBuffer == nullptr)
  {
    Serial.println("Error: LVGL draw buffer allocation failed");
    return false;
  }

  lv_disp_draw_buf_init(&drawBuffer, frameBuffer, nullptr, screenWidth * 20);
  lv_disp_drv_init(&displayDriver);
  displayDriver.hor_res = screenWidth;
  displayDriver.ver_res = screenHeight;
  displayDriver.flush_cb = flushDisplay;
  displayDriver.draw_buf = &drawBuffer;
  lv_disp_drv_register(&displayDriver);

  const esp_timer_create_args_t timerArgs =
  {
    .callback = &tickTask,
    .arg = nullptr,
    .dispatch_method = ESP_TIMER_TASK,
    .name = "lvglTick"
  };

  if (esp_timer_create(&timerArgs, &tickTimer) != ESP_OK)
  {
    Serial.println("Error: LVGL tick timer creation failed");
    return false;
  }

  if (esp_timer_start_periodic(tickTimer, 1000) != ESP_OK)
  {
    Serial.println("Error: LVGL tick timer start failed");
    return false;
  }

  return true;

}   //   begin()

//--- Run the LVGL timer handler regularly from loop()
void DisplayDriver::loop()
{
#if !defined(TEST_DISPLAY)
  lv_timer_handler();
#endif

}   //   loop()

//--- Draw paged diagnostics to identify compatible display driver settings
void DisplayDriver::runTestPattern()
{
#if defined(TEST_DISPLAY)
  static uint8_t page = 0;
  static uint32_t lastPageMs = 0;
  static uint8_t lastDrawnPage = 255;
  static constexpr uint32_t kTestPageIntervalMs = 4500;
  const uint32_t now = millis();

  if ((now - lastPageMs) >= kTestPageIntervalMs)
  {
    lastPageMs = now;
    page = static_cast<uint8_t>((page + 1) % 4);
  }

  if (page == lastDrawnPage)
  {
    return;
  }

  lastDrawnPage = page;

  const int16_t screenWidth = static_cast<int16_t>(tft.width());
  const int16_t screenHeight = static_cast<int16_t>(tft.height());

  tft.startWrite();

  if (page == 0)
  {
    const int16_t barWidth = screenWidth / 6;
    tft.fillRect(0 * barWidth, 0, barWidth, screenHeight, 0xF800);
    tft.fillRect(1 * barWidth, 0, barWidth, screenHeight, 0x07E0);
    tft.fillRect(2 * barWidth, 0, barWidth, screenHeight, 0x001F);
    tft.fillRect(3 * barWidth, 0, barWidth, screenHeight, 0xFFE0);
    tft.fillRect(4 * barWidth, 0, barWidth, screenHeight, 0xF81F);
    tft.fillRect(5 * barWidth, 0, screenWidth - (5 * barWidth), screenHeight, 0x07FF);
  }
  else if (page == 1)
  {
    for (int16_t y = 0; y < screenHeight; y++)
    {
      const uint8_t level = static_cast<uint8_t>((y * 255) / (screenHeight - 1));
      const uint16_t color = static_cast<uint16_t>(((level >> 3) << 11) | ((level >> 2) << 5) | (level >> 3));
      tft.drawFastHLine(0, y, screenWidth, color);
    }
  }
  else if (page == 2)
  {
    tft.fillScreen(0x0000);

    for (int16_t x = 0; x < screenWidth; x += 16)
    {
      tft.drawFastVLine(x, 0, screenHeight, 0x7BEF);
    }

    for (int16_t y = 0; y < screenHeight; y += 16)
    {
      tft.drawFastHLine(0, y, screenWidth, 0x7BEF);
    }

    tft.drawLine(0, 0, screenWidth - 1, screenHeight - 1, 0xF800);
    tft.drawLine(screenWidth - 1, 0, 0, screenHeight - 1, 0x001F);
    tft.drawRect(0, 0, screenWidth, screenHeight, 0xFFFF);

    //-- Corner markers help identify rotation without reading text
    const int16_t markerSize = 20;
    tft.fillRect(0, 0, markerSize, markerSize, 0xF800);
    tft.fillRect(screenWidth - markerSize, 0, markerSize, markerSize, 0x07E0);
    tft.fillRect(0, screenHeight - markerSize, markerSize, markerSize, 0x001F);
    tft.fillRect(screenWidth - markerSize, screenHeight - markerSize, markerSize, markerSize, 0xFFE0);
  }
  else
  {
    tft.fillScreen(0x0000);
    tft.setTextSize(2);
    tft.setTextColor(0xFFFF, 0x0000);
    tft.setCursor(8, 8);

#if defined(CYD_VARIANT_ST7789)
    tft.println("Driver: ST7789");
#else
    tft.println("Driver: ILI9341");
#endif

    tft.printf("TEST_DISPLAY: %d\n", 1);
    tft.printf("Rotation: %u\n", static_cast<unsigned int>(kDisplayRotation));
    tft.printf("Offset X/Y: %d/%d\n", static_cast<int>(kDisplayOffsetX), static_cast<int>(kDisplayOffsetY));
    tft.printf("RGB order: %u\n", static_cast<unsigned int>(kDisplayRgbOrder));
    tft.printf("Invert: %u\n", static_cast<unsigned int>(kDisplayInvert));
    tft.printf("Res: %dx%d\n", static_cast<int>(screenWidth), static_cast<int>(screenHeight));
    tft.println("Page: INFO");
  }

  tft.endWrite();
#endif

}   //   runTestPattern()

//--- Return the active display width
uint16_t DisplayDriver::width() const
{
  return tft.width();

}   //   width()

//--- Return the active display height
uint16_t DisplayDriver::height() const
{
  return tft.height();

}   //   height()
