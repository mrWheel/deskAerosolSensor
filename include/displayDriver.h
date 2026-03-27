#pragma once

#include <Arduino.h>
#include <lvgl.h>
#include <LovyanGFX.hpp>
#include <esp_timer.h>

class DisplayDriver
{
public:
  bool begin();
  void loop();
  void runTestPattern();
  uint16_t width() const;
  uint16_t height() const;

private:
  class CydDisplay : public lgfx::LGFX_Device
  {
  public:
    CydDisplay();

  private:
#if defined(CYD_VARIANT_ST7789)
    lgfx::Panel_ST7789 panel;
#else
    lgfx::Panel_ILI9341 panel;
#endif
    lgfx::Bus_SPI bus;
    lgfx::Light_PWM light;
  };

  static void flushDisplay(lv_disp_drv_t* displayDriver, const lv_area_t* area, lv_color_t* colorMap);
  static void tickTask(void* arg);

  static CydDisplay tft;
  static lv_disp_draw_buf_t drawBuffer;
  static lv_disp_drv_t displayDriver;
  static lv_color_t* frameBuffer;
  static esp_timer_handle_t tickTimer;
};
