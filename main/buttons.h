#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdbool.h>

enum buttons{
	BT_CANCEL = 0,
	BT_PRESSED,
};

lv_obj_t * btnx;

int state;

void state_btn(uint8_t state);

bool btn_released(void);

void handle_btn(int button, lv_obj_t* btny, bool* action, int ctrl);

void btn_main(void);

#endif
