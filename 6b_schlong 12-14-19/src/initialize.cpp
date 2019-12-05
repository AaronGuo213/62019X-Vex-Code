#include "main.h"

void initialize() {

    delay(200);
    //Task liftGo(ctrlLift, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "lift control task"); //starts lift slow and hold task
    Task trayGo(ctrlTray, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "tray control task"); //starts tray outtaking and retracting task
    liftSetPoint = getLiftHeight();
    traySetPoint = 0;
    leftIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    rightIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    tray.tare_position();

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

bool autonColor = false;
int autonType = 0;

lv_res_t switchColor(lv_obj_t *btn) {

    static lv_style_t redAlliance, blueAlliance;
    lv_style_copy(&redAlliance, &lv_style_plain);
    redAlliance.body.main_color = LV_COLOR_HEX(0xD42630);
    redAlliance.body.grad_color = LV_COLOR_HEX(0xD42630);
    redAlliance.body.border.width = 2;
    redAlliance.body.radius = 10;
    redAlliance.body.border.color = LV_COLOR_WHITE;
    lv_style_copy(&blueAlliance, &redAlliance);
    blueAlliance.body.main_color = LV_COLOR_HEX(0x0077C9);
    blueAlliance.body.grad_color = LV_COLOR_HEX(0x0077C9);

    autonColor = !autonColor;
    if(autonColor)
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &blueAlliance);
    else
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &redAlliance);

    return LV_RES_OK;

}

lv_res_t selectAuton(lv_obj_t *btnm, const char *txt) {

    if(txt == "4 stack")
        autonType = 0;
    else if(txt == "4 row")
        autonType = 1;
    else if(txt == "skills")
        autonType = 2;
    else if(txt == "none")
        autonType = 3;

}

lv_res_t confirmAuton(lv_obj_t *btn) {

    autonCount = autonColor * 4 + autonType;

}

void competition_initialize() {

    //480 x 240 cortex
    static lv_style_t grey;//, red, blue;
    lv_style_copy(&grey, &lv_style_plain);
    grey.body.main_color = LV_COLOR_HEX(0x828F8F);
    grey.body.grad_color = LV_COLOR_HEX(0x828F8F);
    grey.body.border.width = 2;
    grey.body.radius = 10;
    grey.body.border.color = LV_COLOR_WHITE;

    /*lv_style_copy(&red, &grey);
    red.body.main_color = LV_COLOR_HEX(0xD42630);
    red.body.grad_color = LV_COLOR_HEX(0xD42630);

    lv_style_copy(&blue, &grey);
    blue.body.main_color = LV_COLOR_HEX(0x0077C9);
    blue.body.grad_color = LV_COLOR_HEX(0x0077C9);*/

    static lv_style_t redAlliance, noAlliance;
    lv_style_copy(&redAlliance, &grey);
    redAlliance.body.main_color = LV_COLOR_HEX(0xD42630);
    redAlliance.body.grad_color = LV_COLOR_HEX(0xD42630);
    redAlliance.body.radius = 10;
    lv_style_copy(&noAlliance, &redAlliance);
    noAlliance.body.main_color = LV_COLOR_SILVER;
    noAlliance.body.grad_color = LV_COLOR_SILVER;

    static lv_style_t teamStyle;
    lv_style_copy(&teamStyle, &noAlliance);

    lv_obj_t *teamName = lv_ta_create(lv_scr_act(), NULL);
    lv_obj_set_size(teamName, 265, 75);
    lv_obj_set_pos(teamName, 210, 5);
    lv_ta_set_cursor_type(teamName, LV_CURSOR_NONE);
    lv_ta_set_style(teamName, LV_TA_STYLE_BG, &teamStyle);
    lv_ta_set_text(teamName, "62019X");

    lv_obj_t *color = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(color, 200, 75);
    lv_btn_set_style(color, LV_BTN_STYLE_REL, &redAlliance);
    lv_btn_set_style(color, LV_BTN_STYLE_PR, &noAlliance);
    lv_obj_align(color, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5);
    lv_obj_t *colorLabel = lv_label_create(color, NULL);
    lv_label_set_text(colorLabel, "Alliance Color");
    lv_btn_set_action(color, LV_BTN_ACTION_CLICK, switchColor);

    static const char *autons[] = {"4 stack", "skills", "\n", "4 row", "none", ""};
    lv_obj_t *auton = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_map(auton, autons);
    lv_obj_set_size(auton, 200, 150);
    lv_obj_set_pos(auton, 5, 85);
    lv_btnm_set_toggle(auton, true, 3);
    lv_btnm_set_action(auton, selectAuton);

    lv_obj_t *confirm = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(confirm, 265, 150);
    lv_obj_set_pos(confirm, 210, 85);
    lv_obj_t *confirmLabel = lv_label_create(confirm, NULL);
    lv_label_set_text(confirmLabel, "CONFRIM AUTON");
    lv_btn_set_action(confirm, LV_BTN_ACTION_CLICK, confirmAuton);

    /*lv_obj_t *colorText = lv_ta_create(lv_scr_act(), NULL);
    lv_obj_set_size(colorText, 150, 50);
    lv_obj_align(colorText, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
    lv_ta_set_cursor_type(colorText, LV_CURSOR_NONE);
    lv_ta_set_text(colorText, "Alliance Color: ");

    lv_obj_t *color = lv_sw_create(lv_scr_act(), NULL);
    lv_obj_set_size(color, 60, 30);
    lv_sw_set_style(color, LV_SW_STYLE_BG, &red);
    lv_sw_set_style(color, LV_SW_STYLE_KNOB_OFF, &red);
    lv_sw_set_style(color, LV_SW_STYLE_INDIC, &blue);
    lv_sw_set_style(color, LV_SW_STYLE_KNOB_ON, &blue);
    lv_sw_off(color);
    lv_obj_set_pos(color, 160, 10);*/

    /*lv_obj_t *modeText = lv_ta_create(lv_scr_act(), NULL);
    lv_obj_set_size(modeText, 100, 50);
    lv_obj_align(modeText, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 100);
    lv_ta_set_cursor_type(modeText, LV_CURSOR_NONE);
    lv_ta_set_text(modeText, "Select Auton: ");

    lv_obj_t *mode = lv_slider_create(lv_scr_act(), NULL);
    lv_obj_set_width(mode, LV_DPI * 2);
    lv_obj_set_pos(mode, 100, 100);
    lv_slider_set_range(mode, 0, 2);
    lv_slider_set_value(mode, 1);*/


    /*std::vector<std::vector<lv_style_t*>> tileData = {
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