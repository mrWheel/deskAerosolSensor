# SEN66 Dashboard for CYD ILI9341

This PlatformIO project targets a CYD style ESP32 board with an ILI9341 display and a 3x3 LVGL dashboard.

## Included environments

- `cyd_ili9341`
  - Main runtime environment for ILI9341
  - Uses the calibrated display configuration
  - Currently includes `SIMULATION=1` for sensor-free visual testing
- `ili9341_r4`
  - Display validation environment with `TEST_DISPLAY=1`
  - Shows diagnostic pages (color bars, grid, corner markers, info)

## Display calibration summary

The panel is stable with:

- `CYD_LCD_ROTATION=4`
- `CYD_LCD_PANEL_WIDTH=320`
- `CYD_LCD_PANEL_HEIGHT=240`
- `CYD_LCD_RGB_ORDER=1`

See [ili9341.md](ili9341.md) for full details.

## Sensor wiring for runtime mode

Default I2C pins in `cyd_ili9341`:

- SEN66 VDD -> 3V3
- SEN66 GND -> GND
- SEN66 SDA -> GPIO21
- SEN66 SCL -> GPIO22

## Simulation mode

When `SIMULATION=1` is enabled:

- sensor read logic is skipped
- all nine tiles are updated with synthetic values
- each tile follows a different up/down waveform
- values do not peak at the same time, making color transitions easy to inspect

## Build and upload

Examples:

- Build main runtime:
  - `platformio run -e cyd_ili9341`
- Upload main runtime:
  - `platformio run -e cyd_ili9341 --target upload`
- Build display test:
  - `platformio run -e ili9341_r4`

## Dashboard tiles

- CO2
- PM2.5
- VOC
- PM1.0
- PM4.0
- PM10
- Temp
- Hum
- NOx

Tile value colors move from cooler to warmer tones as badness increases.
