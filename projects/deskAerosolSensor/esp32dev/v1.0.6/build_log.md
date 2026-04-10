# Build log for cyd_ili9341

Generated: 2026-04-10T13:33:12

$ pio run -e cyd_ili9341
Processing cyd_ili9341 (board: esp32dev; platform: espressif32 @ ^6.12.0; framework: arduino)
--------------------------------------------------------------------------------
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/esp32dev.html
PLATFORM: Espressif 32 (6.13.0) > Espressif ESP32 Dev Module
HARDWARE: ESP32 240MHz, 320KB RAM, 4MB Flash
DEBUG: Current (cmsis-dap) External (cmsis-dap, esp-bridge, esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
PACKAGES: 
 - framework-arduinoespressif32 @ 3.20017.241212+sha.dcc1105b 
 - tool-esptoolpy @ 2.41100.0 (4.11.0) 
 - toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
Found 40 compatible libraries
Scanning dependencies...
Dependency Graph
|-- lvgl @ 8.3.11
|-- LovyanGFX @ 1.2.19
|-- TFT_eSPI @ 2.5.43
|-- Sensirion I2C SEN66 @ 1.2.0
|-- WiFiManager @ 2.0.17
|-- PubSubClient @ 2.8.0
|-- Preferences @ 2.0.0
|-- WiFi @ 2.0.0
|-- WiFiClientSecure @ 2.0.0
|-- Wire @ 2.0.0
Building in release mode
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/Fonts/IPA/lgfx_font_japan.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/Fonts/efont/lgfx_efont_cn.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/Fonts/efont/lgfx_efont_ja.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/Fonts/efont/lgfx_efont_kr.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/Fonts/efont/lgfx_efont_tw.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/utility/lgfx_miniz.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/utility/lgfx_pngle.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/utility/lgfx_qoi.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/utility/lgfx_qrcode.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/utility/lgfx_tjpgd.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/LGFXBase.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/LGFX_Button.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/LGFX_Sprite.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/lgfx_fonts.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/misc/DividedFrameBuffer.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/misc/SpriteBuffer.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/misc/common_function.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/misc/pixelcopy.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_AMOLED.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_Device.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_EPDiy.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_FlexibleFrameBuffer.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_FrameBufferBase.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_GDEW0154D67.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_GDEW0154M09.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_HUB75.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_HasBuffer.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_ILI9225.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_IT8951.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_LCD.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_M5HDMI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_M5UnitGLASS.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_M5UnitLCD.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_NT35510.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_NV3041A.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_RA8875.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_RM68120.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_SH8601Z.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_SSD1306.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_SSD1327.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_SSD1331.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_SSD1351.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_SSD1963.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/panel/Panel_SharpLCD.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/arduino_default/Bus_SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/arduino_default/Bus_Stream.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/arduino_default/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/Bus_EPD.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/Bus_HUB75.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/Bus_I2C.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/Bus_Parallel8.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/Bus_SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/Light_PWM.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/Panel_CVBS.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/Panel_EPD.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32c3/Bus_Parallel8.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32p4/Bus_DSI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32p4/Panel_DSI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32p4/Touch_ST7123.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32s2/Bus_Parallel16.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32s2/Bus_Parallel8.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32s3/Bus_Parallel16.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32s3/Bus_Parallel8.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32s3/Bus_RGB.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp32s3/Panel_RGB.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp8266/Bus_I2C.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp8266/Bus_SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/esp8266/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/framebuffer/Panel_fb.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/framebuffer/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/opencv/Panel_OpenCV.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/opencv/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/rp2040/Bus_I2C.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/rp2040/Bus_SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/rp2040/Light_PWM.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/rp2040/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/samd21/Bus_I2C.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/samd21/Bus_SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/samd21/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/samd51/Bus_I2C.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/samd51/Bus_SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/samd51/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/sdl/Panel_sdl.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/sdl/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/spresense/Bus_SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/spresense/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/stm32/Bus_SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/platforms/stm32/common.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_CHSC6x.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_CSTxxx.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_FT5x06.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_GSLx680.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_GT911.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_NS2009.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_RA8875.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_STMPE610.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_TT21xxx.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib20a/LovyanGFX/lgfx/v1/touch/Touch_XPT2046.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/src/WiFiManagerExt.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/src/colorScale.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/src/dashboardUi.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/src/displayDriver.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/src/main.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/src/sensorReader.cpp.o
Building .pio.nosync/build/cyd_ili9341/bootloader.bin
Generating partitions .pio.nosync/build/cyd_ili9341/partitions.bin
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_disp.c.o
esptool.py v4.11.0
Creating esp32 image...
Merged 1 ELF section
Successfully created esp32 image.
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_event.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_group.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_indev.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_indev_scroll.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_obj.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_obj_class.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_obj_draw.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_obj_pos.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_obj_scroll.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_obj_style.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_obj_style_gen.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_obj_tree.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_refr.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/core/lv_theme.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/arm2d/lv_gpu_arm2d.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_arc.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_img.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_label.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_layer.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_line.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_mask.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_rect.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_transform.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_draw_triangle.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_img_buf.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_img_cache.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/lv_img_decoder.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/pxp/lv_draw_pxp.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/pxp/lv_draw_pxp_blend.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/pxp/lv_gpu_nxp_pxp.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/vglite/lv_draw_vglite.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/vglite/lv_draw_vglite_arc.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/vglite/lv_draw_vglite_blend.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/vglite/lv_draw_vglite_line.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/vglite/lv_draw_vglite_rect.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/vglite/lv_vglite_buf.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/nxp/vglite/lv_vglite_utils.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/renesas/lv_gpu_d2_draw_label.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/renesas/lv_gpu_d2_ra6m3.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_arc.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_bg.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_composite.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_img.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_label.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_layer.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_line.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_mask.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_polygon.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_rect.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_stack_blur.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_texture_cache.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sdl/lv_draw_sdl_utils.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/stm32_dma2d/lv_gpu_stm32_dma2d.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_arc.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_blend.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_dither.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_gradient.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_img.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_layer.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_letter.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_line.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_polygon.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_rect.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/sw/lv_draw_sw_transform.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/draw/swm341_dma2d/lv_gpu_swm341_dma2d.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/layouts/flex/lv_flex.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/layouts/grid/lv_grid.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/bmp/lv_bmp.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/ffmpeg/lv_ffmpeg.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/freetype/lv_freetype.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/fsdrv/lv_fs_fatfs.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/fsdrv/lv_fs_littlefs.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/fsdrv/lv_fs_posix.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/fsdrv/lv_fs_stdio.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/fsdrv/lv_fs_win32.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/gif/gifdec.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/gif/lv_gif.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/png/lodepng.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/png/lv_png.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/qrcode/lv_qrcode.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/qrcode/qrcodegen.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/rlottie/lv_rlottie.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/sjpg/lv_sjpg.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/sjpg/tjpgd.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/libs/tiny_ttf/lv_tiny_ttf.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/lv_extra.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/others/fragment/lv_fragment.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/others/fragment/lv_fragment_manager.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/others/gridnav/lv_gridnav.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/others/ime/lv_ime_pinyin.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/others/imgfont/lv_imgfont.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/others/monkey/lv_monkey.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/others/msg/lv_msg.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/others/snapshot/lv_snapshot.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/themes/basic/lv_theme_basic.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/themes/default/lv_theme_default.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/themes/mono/lv_theme_mono.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/animimg/lv_animimg.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/calendar/lv_calendar.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/calendar/lv_calendar_header_arrow.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/calendar/lv_calendar_header_dropdown.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/chart/lv_chart.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/colorwheel/lv_colorwheel.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/imgbtn/lv_imgbtn.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/keyboard/lv_keyboard.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/led/lv_led.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/list/lv_list.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/menu/lv_menu.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/meter/lv_meter.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/msgbox/lv_msgbox.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/span/lv_span.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/spinbox/lv_spinbox.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/spinner/lv_spinner.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/tabview/lv_tabview.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/tileview/lv_tileview.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/extra/widgets/win/lv_win.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_dejavu_16_persian_hebrew.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_fmt_txt.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_loader.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_10.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_12.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_12_subpx.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_14.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_16.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_18.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_20.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_22.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_24.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_26.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_28.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_28_compressed.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_30.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_32.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_34.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_36.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_38.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_40.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_42.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_44.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_46.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_48.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_montserrat_8.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_simsun_16_cjk.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_unscii_16.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/font/lv_font_unscii_8.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/hal/lv_hal_disp.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/hal/lv_hal_indev.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/hal/lv_hal_tick.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_anim.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_anim_timeline.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_area.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_async.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_bidi.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_color.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_fs.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_gc.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_ll.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_log.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_lru.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_math.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_mem.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_printf.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_style.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_style_gen.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_templ.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_timer.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_tlsf.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_txt.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_txt_ap.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/misc/lv_utils.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_arc.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_bar.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_btn.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_btnmatrix.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_canvas.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_checkbox.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_dropdown.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_img.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_label.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_line.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_objx_templ.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_roller.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_slider.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_switch.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_table.c.o
Compiling .pio.nosync/build/cyd_ili9341/lib5b0/lvgl/widgets/lv_textarea.c.o
Compiling .pio.nosync/build/cyd_ili9341/libc26/SPI/SPI.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib49c/Wire/Wire.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib25e/FS/FS.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib25e/FS/vfs_api.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/libea2/SPIFFS/SPIFFS.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib5b0/liblvgl.a
Compiling .pio.nosync/build/cyd_ili9341/lib285/LittleFS/LittleFS.cpp.o
Indexing .pio.nosync/build/cyd_ili9341/lib5b0/liblvgl.a
Compiling .pio.nosync/build/cyd_ili9341/libe01/TFT_eSPI/TFT_eSPI.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib49c/libWire.a
Archiving .pio.nosync/build/cyd_ili9341/libc26/libSPI.a
Indexing .pio.nosync/build/cyd_ili9341/libc26/libSPI.a
Indexing .pio.nosync/build/cyd_ili9341/lib49c/libWire.a
Compiling .pio.nosync/build/cyd_ili9341/lib99f/Sensirion Core/SensirionCrc.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib99f/Sensirion Core/SensirionErrors.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib99f/Sensirion Core/SensirionI2CCommunication.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib25e/libFS.a
Indexing .pio.nosync/build/cyd_ili9341/lib25e/libFS.a
Archiving .pio.nosync/build/cyd_ili9341/libea2/libSPIFFS.a
Compiling .pio.nosync/build/cyd_ili9341/lib99f/Sensirion Core/SensirionI2CTxFrame.cpp.o
Indexing .pio.nosync/build/cyd_ili9341/libea2/libSPIFFS.a
Archiving .pio.nosync/build/cyd_ili9341/lib285/libLittleFS.a
Compiling .pio.nosync/build/cyd_ili9341/lib99f/Sensirion Core/SensirionRxFrame.cpp.o
Indexing .pio.nosync/build/cyd_ili9341/lib285/libLittleFS.a
Compiling .pio.nosync/build/cyd_ili9341/lib99f/Sensirion Core/SensirionShdlcCommunication.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib99f/Sensirion Core/SensirionShdlcTxFrame.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib7e6/Sensirion I2C SEN66/SensirionI2cSen66.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFi.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFiAP.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFiClient.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFiGeneric.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFiMulti.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib99f/libSensirion Core.a
Indexing .pio.nosync/build/cyd_ili9341/lib99f/libSensirion Core.a
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFiSTA.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib7e6/libSensirion I2C SEN66.a
Indexing .pio.nosync/build/cyd_ili9341/lib7e6/libSensirion I2C SEN66.a
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFiScan.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFiServer.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib63c/WiFi/WiFiUdp.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/libd6e/DNSServer/DNSServer.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/libec0/ESPmDNS/ESPmDNS.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/libb1c/Update/HttpsOTAUpdate.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/libe01/libTFT_eSPI.a
Indexing .pio.nosync/build/cyd_ili9341/libe01/libTFT_eSPI.a
Compiling .pio.nosync/build/cyd_ili9341/libb1c/Update/Updater.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib5cc/WebServer/Parsing.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib63c/libWiFi.a
Compiling .pio.nosync/build/cyd_ili9341/lib5cc/WebServer/WebServer.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/lib5cc/WebServer/detail/mimetable.cpp.o
Indexing .pio.nosync/build/cyd_ili9341/lib63c/libWiFi.a
Compiling .pio.nosync/build/cyd_ili9341/lib3a7/WiFiManager/WiFiManager.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/libd6e/libDNSServer.a
Indexing .pio.nosync/build/cyd_ili9341/libd6e/libDNSServer.a
Compiling .pio.nosync/build/cyd_ili9341/lib841/PubSubClient/PubSubClient.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/liba68/Preferences/Preferences.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/libec0/libESPmDNS.a
Indexing .pio.nosync/build/cyd_ili9341/libec0/libESPmDNS.a
Compiling .pio.nosync/build/cyd_ili9341/lib4e5/WiFiClientSecure/WiFiClientSecure.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/libb1c/libUpdate.a
Compiling .pio.nosync/build/cyd_ili9341/lib4e5/WiFiClientSecure/esp_crt_bundle.c.o
Indexing .pio.nosync/build/cyd_ili9341/libb1c/libUpdate.a
Compiling .pio.nosync/build/cyd_ili9341/lib4e5/WiFiClientSecure/ssl_client.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/Esp.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/FirmwareMSC.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib841/libPubSubClient.a
Archiving .pio.nosync/build/cyd_ili9341/liba68/libPreferences.a
Indexing .pio.nosync/build/cyd_ili9341/lib841/libPubSubClient.a
Indexing .pio.nosync/build/cyd_ili9341/liba68/libPreferences.a
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/FunctionalInterrupt.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/HWCDC.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib5cc/libWebServer.a
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/HardwareSerial.cpp.o
Indexing .pio.nosync/build/cyd_ili9341/lib5cc/libWebServer.a
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/IPAddress.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/IPv6Address.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/MD5Builder.cpp.o
Archiving .pio.nosync/build/cyd_ili9341/lib4e5/libWiFiClientSecure.a
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/Print.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/Stream.cpp.o
Indexing .pio.nosync/build/cyd_ili9341/lib4e5/libWiFiClientSecure.a
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/StreamString.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/Tone.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/USB.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/USBCDC.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/USBMSC.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/WMath.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/WString.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/base64.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/cbuf.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-adc.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-bt.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-cpu.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-dac.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-gpio.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-i2c-slave.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-i2c.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-ledc.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-matrix.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-misc.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-psram.c.o
Archiving .pio.nosync/build/cyd_ili9341/lib3a7/libWiFiManager.a
Indexing .pio.nosync/build/cyd_ili9341/lib3a7/libWiFiManager.a
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-rgb-led.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-rmt.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-sigmadelta.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-spi.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-time.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-timer.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-tinyusb.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-touch.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/esp32-hal-uart.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/firmware_msc_fat.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/libb64/cdecode.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/libb64/cencode.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/main.cpp.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/stdlib_noniso.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/wiring_pulse.c.o
Compiling .pio.nosync/build/cyd_ili9341/FrameworkArduino/wiring_shift.c.o
Archiving .pio.nosync/build/cyd_ili9341/libFrameworkArduino.a
Indexing .pio.nosync/build/cyd_ili9341/libFrameworkArduino.a
Linking .pio.nosync/build/cyd_ili9341/firmware.elf
Retrieving maximum program size .pio.nosync/build/cyd_ili9341/firmware.elf
Checking size .pio.nosync/build/cyd_ili9341/firmware.elf
Advanced Memory Usage is available via "PlatformIO Home > Project Inspect"
RAM:   [===       ]  30.9% (used 101368 bytes from 327680 bytes)
Flash: [=====     ]  45.3% (used 1423537 bytes from 3145728 bytes)
Building .pio.nosync/build/cyd_ili9341/firmware.bin
esptool.py v4.11.0
Creating esp32 image...
Merged 27 ELF sections
Successfully created esp32 image.
========================= [SUCCESS] Took 23.10 seconds =========================

Environment    Status    Duration
-------------  --------  ------------
cyd_ili9341    SUCCESS   00:00:23.104
========================= 1 succeeded in 00:00:23.104 =========================
In file included from .pio.nosync/libdeps/cyd_ili9341/TFT_eSPI/TFT_eSPI.cpp:16:
.pio.nosync/libdeps/cyd_ili9341/TFT_eSPI/TFT_eSPI.h:973:8: warning: #warning >>>>------>> TOUCH_CS pin not defined, TFT_eSPI touch functions will not be available! [-Wcpp]
       #warning >>>>------>> TOUCH_CS pin not defined, TFT_eSPI touch functions will not be available!
        ^~~~~~~

Resolved buildDir: /Users/WillemA/Documents/platformioProjects/deskAerosolSensor/.pio.nosync/build/cyd_ili9341
