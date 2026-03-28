#pragma once

#include <Arduino.h>

//--- Select I2C pins for the external SEN66 sensor
#ifndef CYD_I2C_SDA_PIN
#define CYD_I2C_SDA_PIN 27
#endif

#ifndef CYD_I2C_SCL_PIN
#define CYD_I2C_SCL_PIN 22
#endif

static constexpr uint8_t kI2cSdaPin = CYD_I2C_SDA_PIN;
static constexpr uint8_t kI2cSclPin = CYD_I2C_SCL_PIN;
static constexpr uint8_t kSen66I2cAddress = 0x6B;

//--- Dashboard timing
static constexpr uint32_t kSensorWarmupMs = 2000;

#ifndef UPDATE_INTERVAL
#define UPDATE_INTERVAL 5000
#endif
static constexpr uint32_t kSensorUpdateIntervalMs = static_cast<uint32_t>(UPDATE_INTERVAL);

//--- Display configuration
#ifndef CYD_LCD_ROTATION
#define CYD_LCD_ROTATION 1
#endif

#ifndef CYD_LCD_OFFSET_X
#define CYD_LCD_OFFSET_X 0
#endif

#ifndef CYD_LCD_OFFSET_Y
#define CYD_LCD_OFFSET_Y 0
#endif

#ifndef CYD_LCD_RGB_ORDER
#define CYD_LCD_RGB_ORDER 0
#endif

#ifndef CYD_LCD_INVERT
#define CYD_LCD_INVERT 0
#endif

#ifndef CYD_LCD_PANEL_WIDTH
#define CYD_LCD_PANEL_WIDTH 240
#endif

#ifndef CYD_LCD_PANEL_HEIGHT
#define CYD_LCD_PANEL_HEIGHT 320
#endif

#ifndef CYD_LCD_SPI_WRITE_HZ
#define CYD_LCD_SPI_WRITE_HZ 40000000
#endif

#ifndef CYD_LCD_SPI_READ_HZ
#define CYD_LCD_SPI_READ_HZ 16000000
#endif

static constexpr uint16_t kScreenWidth = 320;
static constexpr uint16_t kScreenHeight = 240;
static constexpr uint8_t kDisplayRotation = CYD_LCD_ROTATION;
static constexpr int16_t kDisplayOffsetX = CYD_LCD_OFFSET_X;
static constexpr int16_t kDisplayOffsetY = CYD_LCD_OFFSET_Y;
static constexpr bool kDisplayRgbOrder = (CYD_LCD_RGB_ORDER != 0);
static constexpr bool kDisplayInvert = (CYD_LCD_INVERT != 0);
static constexpr uint16_t kDisplayPanelWidth = CYD_LCD_PANEL_WIDTH;
static constexpr uint16_t kDisplayPanelHeight = CYD_LCD_PANEL_HEIGHT;
static constexpr uint32_t kDisplaySpiWriteHz = CYD_LCD_SPI_WRITE_HZ;
static constexpr uint32_t kDisplaySpiReadHz = CYD_LCD_SPI_READ_HZ;
