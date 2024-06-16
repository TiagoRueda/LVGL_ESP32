#include "buttons.h"
#include "definitions.h"

void state_btn(uint8_t state){
	switch(state){
	   	case BT_CANCEL:
			lv_obj_remove_style(btnx, &style_button_pressed, 0);
			lv_obj_add_style(btnx, &style_btn, 0);
		break;
	   	case BT_PRESSED:
			lv_obj_remove_style(btnx, &style_btn, 0);
			lv_obj_add_style(btnx, &style_button_pressed, 0);
	   	break;
	}
	state = 0;
}

bool btn_released(){
    return (gpio_get_level(BUTTON_1) == 1 && gpio_get_level(BUTTON_2) == 1 &&
            gpio_get_level(BUTTON_3) == 1 && gpio_get_level(BUTTON_4) == 1);
}

void handle_btn(int button, lv_obj_t* btny, bool* action, int ctrl){
    if ((gpio_get_level(button) == 0 || ctrl_http == ctrl) && click_long == false) {
        btnx = btny;
        state = BT_PRESSED;
        disable = false;
        *action = true;
        click_long = true;
        change_state = 1;
        state_btn(state);
        ctrl_http = 0;
        return;
    }
}

void btn_main(void){
    handle_btn(BUTTON_1, btn1, &bot, 1);
    handle_btn(BUTTON_2, btn2, &up, 2);
    handle_btn(BUTTON_3, btn3, &back, 3);
    handle_btn(BUTTON_4, btn4, &enter, 4);

    if (btn_released() && disable) {
        state = BT_CANCEL;
        up = bot = back = enter = click_long = false;
        if (change_state == 1) {
            state_btn(state);
            change_state = 0;
        }
    }
    disable = true;
}
