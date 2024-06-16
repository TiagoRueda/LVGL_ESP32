#include "definitions.h"

static void style_init(void){
    lv_style_init(&style_btn);
    lv_style_set_radius(&style_btn, 10);
    lv_style_set_bg_opa(&style_btn, LV_OPA_COVER);
    lv_style_set_bg_color(&style_btn, lv_palette_lighten(LV_PALETTE_GREY, 3));
    lv_style_set_bg_grad_color(&style_btn, lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_grad_dir(&style_btn, LV_GRAD_DIR_VER);

    lv_style_set_border_color(&style_btn, lv_color_black());
    lv_style_set_border_opa(&style_btn, LV_OPA_20);
    lv_style_set_border_width(&style_btn, 2);

    lv_style_set_text_color(&style_btn, lv_color_black());

    lv_style_init(&style_button_pressed);
    lv_style_set_radius(&style_button_pressed, 10);
    lv_style_set_bg_opa(&style_button_pressed, LV_OPA_COVER);
    lv_style_set_bg_color(&style_button_pressed, lv_color_hex(0x8b9d9f));
    lv_style_set_bg_grad_color(&style_button_pressed, lv_color_hex(0xe7ebeb));
    lv_style_set_bg_grad_dir(&style_button_pressed, LV_GRAD_DIR_VER);

    lv_style_set_border_color(&style_button_pressed, lv_color_black());
    lv_style_set_border_opa(&style_button_pressed, LV_OPA_20);
    lv_style_set_border_width(&style_button_pressed, 2);

    lv_style_set_text_color(&style_button_pressed, lv_color_black());
}

void btn_obj(void){
    style_init();

    if(btn1 != NULL){
    lv_obj_del(btn1);
    btn1 = NULL;}

    btn1 = lv_btn_create(lv_scr_act());
    lv_obj_remove_style_all(btn1);
    lv_obj_set_pos(btn1, 12, 210);
    lv_obj_set_size(btn1, 70, 30);
    lv_obj_add_style(btn1, &style_btn, 0);
    lv_obj_set_style_bg_img_src(btn1, LV_SYMBOL_DOWN, 0);

    if(btn2 != NULL){
    lv_obj_del(btn2);
    btn2 = NULL;}

    btn2 = lv_btn_create(lv_scr_act());
    lv_obj_remove_style_all(btn2);
    lv_obj_set_pos(btn2, 87, 210);
    lv_obj_set_size(btn2, 70, 30);
    lv_obj_add_style(btn2, &style_btn, 0);
    lv_obj_set_style_bg_img_src(btn2, LV_SYMBOL_UP, 0);

    if(btn3 != NULL){
    lv_obj_del(btn3);
    btn3 = NULL;}

    btn3 = lv_btn_create(lv_scr_act());
    lv_obj_remove_style_all(btn3);
    lv_obj_set_pos(btn3, 162, 210);
    lv_obj_set_size(btn3, 70, 30);
    lv_obj_add_style(btn3, &style_btn, 0);

    label1 = lv_label_create(btn3);
    lv_label_set_text(label1, "BACK");
    lv_obj_center(label1);

    if(btn4 != NULL){
    lv_obj_del(btn4);
    btn4 = NULL;}

    btn4 = lv_btn_create(lv_scr_act());
    lv_obj_remove_style_all(btn4);
    lv_obj_set_pos(btn4, 237, 210);
    lv_obj_set_size(btn4, 70, 30);
    lv_obj_add_style(btn4, &style_btn, 0);

    label2 = lv_label_create(btn4);
    lv_label_set_text(label2, "ENTER");
    lv_obj_center(label2);
}

void lv_list(void){
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_palette_main(LV_PALETTE_GREY));
    lv_obj_add_style(lv_scr_act(), &style_screen, LV_STATE_DEFAULT);

    list1 = lv_list_create(lv_scr_act());
    lv_obj_set_size(list1, 160, 180);
    lv_obj_center(list1);
    lv_obj_align(list1, LV_ALIGN_CENTER, 0, -15);

    lv_list_add_text(list1, "Menu");

    btn[1] = lv_list_add_btn(list1, LV_SYMBOL_BLUETOOTH, "Bluetooth");
    btn[2] = lv_list_add_btn(list1, LV_SYMBOL_WIFI, "WiFi");
    btn[3] = lv_list_add_btn(list1, LV_SYMBOL_DIRECTORY, "Arquivo");
    btn[4] = lv_list_add_btn(list1, LV_SYMBOL_PLUS, "Adicionar");
    btn[5] = lv_list_add_btn(list1, LV_SYMBOL_LIST, "Lista");
    btn[6] = lv_list_add_btn(list1, LV_SYMBOL_EDIT, "Editar");
    btn[7] = lv_list_add_btn(list1, LV_SYMBOL_BATTERY_FULL, "Bateria");
    btn[8] = lv_list_add_btn(list1, LV_SYMBOL_CLOSE, "Voltar");
    menu_select = 1;

    lv_obj_add_state(btn[menu_select], LV_STATE_PRESSED | LV_STATE_CHECKED);

    btn_obj();
}

void update_list(void){
	lv_timer_handler();

	lv_obj_clear_state(btn[menu_select], LV_STATE_PRESSED | LV_STATE_CHECKED);
	if (bot) {
        menu_select = (menu_select + 1 >= 9) ? 1 : menu_select + 1;
        bot = false;
        printf("%d \n", menu_select);
        lv_obj_scroll_to_y(list1, (menu_select >= 5) ? 110 : 0, LV_ANIM_OFF);
	}

	if (up) {
        menu_select = (menu_select - 1 <= 0) ? 8 : menu_select - 1;
        up = false;

        lv_obj_scroll_to_y(list1, (menu_select <= 4) ? 0 : 110, LV_ANIM_OFF);
	}
	lv_obj_add_state(btn[menu_select], LV_STATE_PRESSED | LV_STATE_CHECKED);
}
