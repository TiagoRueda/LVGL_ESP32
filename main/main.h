#ifndef MAIN_H
#define MAIN_H

#include "definitions.h"
#include "lvgl.c"
#include "http.c"
#include "btn_select.c"

#if CONFIG_EXAMPLE_LCD_CONTROLLER_ILI9341
#include "esp_lcd_ili9341.h"
#elif CONFIG_EXAMPLE_LCD_CONTROLLER_GC9A01
#include "esp_lcd_gc9a01.h"
#endif

#if CONFIG_EXAMPLE_LCD_TOUCH_CONTROLLER_STMPE610
#include "esp_lcd_touch_stmpe610.h"
#endif

static const char *TAG = "example";

#define LCD_HOST  SPI2_HOST

#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (20 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_SCLK           18
#define EXAMPLE_PIN_NUM_MOSI           23
#define EXAMPLE_PIN_NUM_MISO           21
#define EXAMPLE_PIN_NUM_LCD_DC         17
#define EXAMPLE_PIN_NUM_LCD_RST        4
#define EXAMPLE_PIN_NUM_LCD_CS         16
#define EXAMPLE_PIN_NUM_BK_LIGHT       32
#define EXAMPLE_PIN_NUM_TOUCH_CS       15

#if CONFIG_EXAMPLE_LCD_CONTROLLER_ILI9341
#define EXAMPLE_LCD_H_RES              320
#define EXAMPLE_LCD_V_RES              240
#elif CONFIG_EXAMPLE_LCD_CONTROLLER_GC9A01
#define EXAMPLE_LCD_H_RES              240
#define EXAMPLE_LCD_V_RES              240
#endif

#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8

#define EXAMPLE_LVGL_TICK_PERIOD_MS    2


#if CONFIG_EXAMPLE_LCD_TOUCH_ENABLED
esp_lcd_touch_handle_t tp = NULL;
#endif

#endif
