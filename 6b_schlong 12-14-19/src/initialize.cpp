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

int autonCount = 3, autonType = 3;
bool autonColor = false, confirmed = false;

void calcAuton() {

    autonCount = autonColor * 4 + autonType;

}

lv_res_t switchColor(lv_obj_t *btn) {

    //Determines which side the robot is on
    static lv_style_t red, blue;
    lv_style_copy(&red, &lv_style_plain);
    red.body.main_color = LV_COLOR_RED;
    red.body.grad_color = LV_COLOR_RED;
    red.body.border.width = 2;
    red.body.radius = 10;
    red.body.border.color = LV_COLOR_WHITE;
    lv_style_copy(&blue, &red);
    blue.body.main_color = LV_COLOR_BLUE;
    blue.body.grad_color = LV_COLOR_BLUE;

    autonColor = !autonColor;
    if(autonColor)
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &blue);
    else
        lv_btn_set_style(btn, LV_BTN_STYLE_REL, &red);

    calcAuton();
    return LV_RES_OK;

}

lv_res_t selectAuton(lv_obj_t *btnm, const char *txt) {

    //Determines which auton is desired
    if(txt == "4 stack")
        autonType = 0;
    else if(txt == "4 row")
        autonType = 1;
    else if(txt == "skills")
        autonType = 2;
    else if(txt == "none")
        autonType = 3;

    calcAuton();

}

lv_res_t confirmAuton(lv_obj_t *btn) {

    //Calculates which auton will be used
    calcAuton();
    confirmed = true;

}

void competition_initialize() { //480 x 240 cortex

    /*================================
    STYLES STYLES STYLES STYLES STYLES
    ================================*/
    static lv_style_t grey, red, blue, redBlue, blueRed, black, green, black2;

    lv_style_copy(&grey, &lv_style_plain);
    grey.body.main_color = LV_COLOR_HEX(0x828F8F);
    grey.body.grad_color = LV_COLOR_HEX(0x828F8F);
    grey.body.border.width = 2;
    grey.body.radius = 10;
    grey.body.border.color = LV_COLOR_WHITE;

    lv_style_copy(&red, &grey);
    red.body.main_color = LV_COLOR_RED;
    red.body.grad_color = LV_COLOR_RED;
    red.body.radius = 10;

    lv_style_copy(&blue, &red);
    blue.body.main_color = LV_COLOR_BLUE;
    blue.body.grad_color = LV_COLOR_BLUE;
    
    lv_style_copy(&redBlue, &red);
    redBlue.body.grad_color = LV_COLOR_BLUE;

    lv_style_copy(&blueRed, &blue);
    blueRed.body.grad_color = LV_COLOR_RED;

    lv_style_copy(&black, &red);
    black.body.main_color = LV_COLOR_BLACK;
    black.body.grad_color = LV_COLOR_BLACK;
    black.body.border.color = LV_COLOR_GRAY;
    black.text.color = LV_COLOR_RED;
    black.text.letter_space = 5;

    lv_style_copy(&green, &grey);
    green.body.main_color = LV_COLOR_GREEN;
    green.body.grad_color = LV_COLOR_GREEN;
    green.body.radius = 50;

    lv_style_copy(&black2, &black);
    black2.body.radius = 0;

    lv_obj_t *sample = lv_btnm_create(lv_scr_act(), NULL);
    lv_obj_set_pos(sample, 500, 250);
    lv_style_t redOutline, blueOutline;
    lv_style_copy(&redOutline, lv_btnm_get_style(sample, LV_BTNM_STYLE_BTN_TGL_REL));
    redOutline.body.radius = 15;
    redOutline.body.border.width = 2;
    redOutline.body.border.color = LV_COLOR_RED;
    lv_style_copy(&blueOutline, &redOutline);
    blueOutline.body.border.color = LV_COLOR_BLUE;

    /*=====================
    62019X LOGO (TEXT AREA)
    =====================*/
    lv_obj_t *teamName = lv_ta_create(lv_scr_act(), NULL);
    lv_obj_set_size(teamName, 230, 40);
    lv_obj_set_pos(teamName, 5, 5);
    lv_ta_set_cursor_type(teamName, LV_CURSOR_NONE);
    lv_ta_set_style(teamName, LV_TA_STYLE_BG, &black);
    lv_ta_set_text(teamName, "62019X");

    /*==============================
    ALLIANCE COLOR SELECTOR (BUTTON)
    ==============================*/
    lv_obj_t *color = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(color, 230, 80);
    lv_btn_set_style(color, LV_BTN_STYLE_REL, &red);
    lv_btn_set_style(color, LV_BTN_STYLE_PR, &redBlue);
    lv_obj_set_pos(color, 5, 50);
    lv_obj_t *colorLabel = lv_label_create(color, NULL);
    lv_label_set_text(colorLabel, "Alliance Color");
    lv_btn_set_action(color, LV_BTN_ACTION_CLICK, switchColor);

    /*=================================
    AUTON TYPE SELECTOR (BUTTON MATRIX)
    =================================*/
    static const char *autons[] = {"4 stack", "skills", "\n", "4 row", "none", ""};
    lv_obj_t *auton = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_map(auton, autons);
    lv_obj_set_size(auton, 230, 125);
    lv_obj_set_pos(auton, 240, 5);
    lv_btnm_set_toggle(auton, true, 3);
    lv_btnm_set_action(auton, selectAuton);

    /*=================================
    CONFIRM BUTTON/DESCRIPTION (BUTTON)
    =================================*/
    lv_obj_t *confirm = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(confirm, 470, 100);
    lv_obj_set_pos(confirm, 5, 135);
    lv_btn_set_style(confirm, LV_BTN_STYLE_PR, &green);
    lv_obj_t *confirmLabel = lv_label_create(confirm, NULL);
    lv_btn_set_action(confirm, LV_BTN_ACTION_CLICK, confirmAuton);
    lv_label_set_align(confirmLabel, LV_LABEL_ALIGN_CENTER);
    const char *stackDesc = "8 cubes in the outer stack of the big goal.\nGets the preload, the cube in front, the 4 stack,\nthe cube next to the tower, and the stray cube.\nCLICK TO CONFIRM";
    const char *rowDesc = "8 cubes in the small goal.\nGets the preload, the 3 grounded cubes\nfrom the long L, and the 4 cubes in a row.\nCLICK TO CONFIRM";
    const char *skillsDesc = "\nDescription not available.\n\nCLICK TO CONFIRM";
    const char *noneDesc = "\nNo auton. Loser.\n\nCLICK TO CONFIRM";
    while(!confirmed) {
        switch(autonType) {
            case 0:
                lv_label_set_text(confirmLabel, stackDesc);
                break;
            case 1:
                lv_label_set_text(confirmLabel, rowDesc);
                break;
            case 2:
                lv_label_set_text(confirmLabel, skillsDesc);
                break;
            case 3:
                lv_label_set_text(confirmLabel, noneDesc);
                break;
        }
        if(autonColor) {
            lv_btn_set_style(color, LV_BTN_STYLE_PR, &blueRed);
            lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_TGL_PR, &blueOutline);
            //lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_PR, &blue);
            lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_TGL_REL, &blueOutline);
        }
        else {
            lv_btn_set_style(color, LV_BTN_STYLE_PR, &redBlue);
            lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_TGL_PR, &redOutline);
            //lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_PR, &redOutline);
            lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_TGL_REL, &redOutline);
        }
        delay(100);
    }

    /*=======================
    COVER AFTER AUTON CONFIRM
    =======================*/
    lv_obj_t *cover = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_pos(cover, 0, 0);
    lv_obj_set_size(cover, 480, 240);
    black.body.radius = 0;
    lv_obj_set_style(cover, &black2);
    lv_obj_t *coverLabel = lv_label_create(cover, NULL);
    lv_label_set_align(coverLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(coverLabel, "GO GET EM BOYS");

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