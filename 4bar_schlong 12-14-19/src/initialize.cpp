#include "main.h"

void initialize() {

    delay(200);
    Task liftGo(liftCtrl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "lift control task"); //starts lift slow and hold task
    //Task trayGo(trayCtrl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "tray control task"); //starts tray outtaking and retracting task
    liftSetPoint = getLiftHeight();
    leftIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    rightIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);

}

int autonCount = 0;

/*void lcdScroll() {

    if(autonCount > 6) { //loops the options

        autonCount = 0;

    }

    else if(autonCount < 0) { //loops the options

        autonCount = 6;

    }

    switch(autonCount) {

        case 0:
            lcd::set_text(2, "RED1\n");
            lcd::set_text(1, "4 Stack, 6 Cubes in Big Goal");
            break;

        case 1:
            lcd::set_text(2, "RED2\n");
            lcd::set_text(1, "Long L, 4 Cubes Unscored");
            break;

        case 2:
            lcd::set_text(2, "RED3\n");
            lcd::set_text(1, "4 in a Row, 5 Cubes in Small Goal");
            break;

        case 3:
            lcd::set_text(1, "No Auton\n");
            break;

        case 4:
            lcd::set_text(2, "BLUE1\n");
            lcd::set_text(1, "4 Stack, 6 Cubes in Big Goal");
            break;
            
        case 5:
            lcd::set_text(2, "BLUE2\n");
            lcd::set_text(1, "Long L, 4 Cubes Unscored");
            break;

        case 6:
            lcd::set_text(2, "BLUE3\n");
            lcd::set_text(1, "4 in a Row, 5 Cubes in Small Goal");
            break;

        default:
            lcd::set_text(1, "ERROR");
            break;

    }

}

void on_left_pressed() {

    autonCount--;
    lcdScroll();

}

void on_center_pressed() {

    lcd::shutdown();

}

void on_right_pressed() {

    autonCount++;
    lcdScroll();

}*/

void competition_initialize() {

    lv_obj_t *colorText = lv_ta_create(lv_scr_act(), NULL);
    lv_obj_set_size(colorText, 100, 50);
    lv_obj_align(colorText, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_ta_set_cursor_type(colorText, LV_CURSOR_NONE);
    lv_ta_set_text(colorText, "Alliance Color: ");

    lv_obj_t *color = lv_sw_create(lv_scr_act(), NULL);
    lv_sw_off(color);
    lv_obj_set_pos(color, 150, 25);

    lv_obj_t *modeText = lv_ta_create(lv_scr_act(), NULL);
    lv_obj_set_size(modeText, 100, 50);
    lv_obj_align(modeText, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 100);
    lv_ta_set_cursor_type(modeText, LV_CURSOR_NONE);
    lv_ta_set_text(modeText, "Select Auton: ");

    lv_obj_t *mode = lv_slider_create(lv_scr_act(), NULL);
    lv_obj_set_width(mode, LV_DPI * 2);
    lv_obj_set_pos(mode, 100, 100);
    lv_slider_set_range(mode, 0, 2);
    lv_slider_set_value(mode, 1);


    /*lv_style_t grey, red, blue;
    lv_style_copy(&grey, &lv_style_plain);
    grey.body.main_color = LV_COLOR_HEX(0x828F8F);
    grey.body.grad_color = LV_COLOR_HEX(0x828F8F);
    grey.body.border.width = 1;
    grey.body.radius = 0;
    grey.body.border.color = LV_COLOR_WHITE;

    lv_style_copy(&red, &grey);
    red.body.main_color = LV_COLOR_HEX(0xD42630);
    red.body.grad_color = LV_COLOR_HEX(0xD42630);

    lv_style_copy(&blue, &grey);
    blue.body.main_color = LV_COLOR_HEX(0x0077C9);
    blue.body.grad_color = LV_COLOR_HEX(0x0077C9);

    std::vector<std::vector<lv_style_t*>> tileData = {
        {&grey, &red , &grey, &grey, &blue, &grey},
        {&red , &grey, &grey, &grey, &grey, &blue},
        {&grey, &grey, &grey, &grey, &grey, &grey},
        {&grey, &grey, &grey, &grey, &grey, &grey},
        {&grey, &grey, &grey, &grey, &grey, &grey},
        {&grey, &grey, &grey, &grey, &grey, &grey}
    };

    lv_obj_t* field = lv_obj_create(lv_scr_act(), NULL);
    int fieldLength = lv_obj_get_height(field);
    int tileLength = fieldLength / 6;
    for(int y = 0; y < 6; y++) {
        for(int x = 0; x < 6; x++) {
            lv_obj_t* tileObj = lv_btn_create(lv_scr_act(), NULL);
            lv_obj_set_size(tileObj, tileLength ,tileLength);
            lv_obj_set_pos(tileObj, x * tileLength, y * tileLength);
            lv_obj_set_style(tileObj, tileData[y][x]);
        }
    }*/


    /*lcd::initialize();
    lcd::set_text(0, "choose auton");
    lcdScroll();
    lcd::register_btn0_cb(on_left_pressed);
    lcd::register_btn1_cb(on_center_pressed);
    lcd::register_btn2_cb(on_right_pressed);*/

}

void disabled() {

    

}