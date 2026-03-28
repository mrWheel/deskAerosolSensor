# SEN66 Dashboard for CYD ILI9341

This PlatformIO project targets a CYD style ESP32 board with an ILI9341 display and a 3x3 LVGL dashboard.

## Included environments

- `cyd_ili9341`
  - Main runtime environment for ILI9341
  - Uses the calibrated display configuration
  - `UPDATE_INTERVAL=2500` (milliseconds)
  - `SIMULATION` to show simulated data without using the SEN66
  
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
- SEN66 SDA -> GPIO27
- SEN66 SCL -> GPIO22

Important: on the ILI9341 variant, using GPIO21 for SDA conflicts with the display backlight pin and can make the screen appear black.

## Simulation mode

When `SIMULATION=1` is enabled:

- sensor read logic is skipped
- all nine tiles are updated with synthetic values
- each tile follows a different up/down waveform
- values do not peak at the same time, making color transitions easy to inspect

## Runtime timing

- `UPDATE_INTERVAL` is in milliseconds (ms)
- Set it in `platformio.ini` via build flag, for example:
  - `-D UPDATE_INTERVAL=2500` for 2.5 s
  - `-D UPDATE_INTERVAL=5000` for 5.0 s

The dashboard still shows human-readable time in seconds in the header.

## UI behavior notes

- Header status text uses a fixed position block to avoid left/right jumping when line lengths change.
- The second status line (`Just updated` / `Updated ...`) is tuned to sit close under the first line.
- The existing vertical line at the right side of each tile (LVGL scrollbar part) follows the same color as the tile value.

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

Tile value colors move from cooler (blue) to warmer tones (red) as badness increases.
