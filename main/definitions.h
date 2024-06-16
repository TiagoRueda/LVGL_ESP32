#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_log.h"
#include "lvgl.h"

static lv_style_t style_btn;
static lv_style_t style_screen;
static lv_style_t style_button_pressed;
lv_obj_t * list1;
lv_obj_t * btn[9];
lv_obj_t * btn1;
lv_obj_t * btn2;
lv_obj_t * btn3;
lv_obj_t * btn4;
lv_obj_t * label1;
lv_obj_t * label2;
int8_t menu_select;
int8_t change_state;
bool click_long = false;
bool disable = true;
bool up = false;
bool bot = false;
bool back = false;
bool enter = false;

#define BUTTON_1 GPIO_NUM_13
#define BUTTON_2 GPIO_NUM_12
#define BUTTON_3 GPIO_NUM_14
#define BUTTON_4 GPIO_NUM_27

#endif
