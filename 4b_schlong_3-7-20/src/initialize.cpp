#include "main.h"

void initialize() {

    brakeIntk(); //makes intake hold their position
    tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    tray.tare_position(); //resets the motor position values
    lift.tare_position();
    if(!isSkills) {
        resetGyro();
        delay(500);
        while(imu.is_calibrating())
            delay(50);
        delay(2000);
    }
    startingZero = -imu.get_yaw();
    std::cout << startingZero << std::endl;
    //initiates the control tasks
    Task liftGo(ctrlLift, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "lift control task"); //starts lift slow and hold task
    Task trayGo(ctrlTray, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "tray control task"); //starts tray outtaking and retracting task
    liftSetPoint = getLiftHeight();
    traySetPoint = 0;

}

/*============
AUTON SELECTOR
============*/

int autonCount = 10, autonType = 10;
bool autonColor = false, confirmed = false;

/*======================
STYLE CREATION FUNCTIONS
======================*/

lv_style_t lvMakeStyle(lv_style_t copy, lv_color_t mainColor, lv_color_t gradColor, int radius = -1) {

    lv_style_t style;
    lv_style_copy(&style, &copy);
    style.body.main_color = mainColor;
    style.body.grad_color = gradColor;
    if(radius != -1)
        style.body.radius = radius;
    return style;

}

lv_style_t lvSetBorder(lv_style_t style, lv_color_t color, int thickness = -1) {

    style.body.border.color = color;
    if(thickness != -1)
        style.body.border.width = thickness;
    return style;

}

lv_style_t lvSetText(lv_style_t style, lv_color_t txtColor, lv_font_t *font, int spaceSize = -1, int lineSize = -1) {

    style.text.color = txtColor;
    style.text.font = font;
    if(spaceSize != -1)
        style.text.letter_space = spaceSize;
    if(lineSize != -1)
        style.text.line_space = lineSize;
    return style;

}

/*===========================
ACTIONS FUNCTIONS FOR BUTTONS
===========================*/

void calcAuton() {

    autonCount = autonColor * 5 + autonType;

}

lv_res_t switchColor(lv_obj_t *btn) {

    //Determines which side the robot is on
    static lv_style_t red, blue;
    red = lvMakeStyle(lv_style_plain, LV_COLOR_RED, LV_COLOR_RED, 10);
    red = lvSetBorder(red, LV_COLOR_WHITE, 2);
    blue = lvMakeStyle(red, LV_COLOR_BLUE, LV_COLOR_BLUE);

    autonColor = !autonColor;
    lv_btn_set_style(btn, LV_BTN_STYLE_REL, autonColor ? &blue : &red);
    calcAuton();
    return LV_RES_OK;

}

lv_res_t selectAuton(lv_obj_t *btnm, const char *txt) {

    //Determines which auton is desired
    if(txt == "stack-8")
        autonType = 0;
    else if(txt == "row-7")
        autonType = 1;
    else if(txt == "row-6")
        autonType = 2;
    else if(txt == "stack-7")
        autonType = 3;
    else if(txt == "skills")
        autonType = 4;
    else if(txt == "none")
        autonType = 10;

    calcAuton();
    return LV_RES_OK;

}

lv_res_t confirmAuton(lv_obj_t *btn) {

    //locks the auton so it can't be changed
    calcAuton();
    confirmed = true;
    return LV_RES_OK;

}

/*=====================================
INTIALIZE (RUNS WHEN ROBOT IS DISABLED)
=====================================*/

void competition_initialize() { //480 x 240 cortex

    /*================================
    STYLES STYLES STYLES STYLES STYLES
    ================================*/
    static lv_style_t red, blue, redBlue, blueRed, black, black2, black3;

    red = lvMakeStyle(lv_style_plain, LV_COLOR_RED, LV_COLOR_RED, 10);
    red = lvSetBorder(red, LV_COLOR_WHITE, 2);
    blue = lvMakeStyle(red, LV_COLOR_BLUE, LV_COLOR_BLUE);
    redBlue = lvMakeStyle(red, LV_COLOR_RED, LV_COLOR_BLUE);
    blueRed = lvMakeStyle(blue, LV_COLOR_BLUE, LV_COLOR_RED);
    black = lvMakeStyle(red, LV_COLOR_BLACK, LV_COLOR_RED);
    black = lvSetBorder(black, LV_COLOR_GRAY);
    black = lvSetText(black, LV_COLOR_WHITE, &lv_font_dejavu_20, 5);
    black2 = lvMakeStyle(black, LV_COLOR_BLACK, LV_COLOR_RED, 50);
    black3 = lvMakeStyle(black, LV_COLOR_BLACK, LV_COLOR_BLACK, 0);

    lv_obj_t *sample = lv_btnm_create(lv_scr_act(), NULL);
    lv_obj_set_pos(sample, 500, 250);
    lv_style_t redOutline, blueOutline;
    lv_style_copy(&redOutline, lv_btnm_get_style(sample, LV_BTNM_STYLE_BTN_TGL_REL));
    redOutline.body.radius = 15;
    redOutline = lvSetBorder(redOutline, LV_COLOR_RED, 2);
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
    static const char *autons[] = {"stack-8", "row-7", "skills", "\n", "stack-7", "row-6", "none", ""};
    lv_obj_t *auton = lv_btnm_create(lv_scr_act(), NULL);
    lv_btnm_set_map(auton, autons);
    lv_obj_set_size(auton, 230, 125);
    lv_obj_set_pos(auton, 240, 5);
    lv_btnm_set_toggle(auton, true, 5);
    lv_btnm_set_action(auton, selectAuton);

    /*=================================
    CONFIRM BUTTON/DESCRIPTION (BUTTON)
    =================================*/
    lv_obj_t *confirm = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(confirm, 470, 100);
    lv_obj_set_pos(confirm, 5, 135);
    lv_btn_set_style(confirm, LV_BTN_STYLE_PR, &black2);
    lv_obj_t *confirmLabel = lv_label_create(confirm, NULL);
    lv_btn_set_action(confirm, LV_BTN_ACTION_CLICK, confirmAuton);
    lv_label_set_align(confirmLabel, LV_LABEL_ALIGN_CENTER);
    const char *stack8Desc = "8 cubes in the outer stack of the big goal.\nGets the preload, the cube in front, the 4 stack,\nthe cube next to the tower, and the stray cube.\nCLICK TO CONFIRM";
    const char *row7Desc = "7 cubes in the small goal.\nGets the preload, 2 cubes from \nthe long L, and the row of 4.\nCLICK TO CONFIRM";
    const char *row6Desc = "6 cubes in the small goal.\nGets the preload, the row of 4,\n and the cube under the tower.\nCLICK TO CONFIRM";
    const char *stack7Desc = "7 cubes in the outer stack of the big goal.\nGets the preload, the cube in front,\nthe 4 stack, and the stray cube.\nCLICK TO CONFIRM";
    const char *skillsDesc = "8 cubes in the small goal and 3 towers.\n8 cube auton from the L and row,\n then gets the three nearest towers.\nCLICK TO CONFIRM";
    const char *noneDesc = "\nNo auton. Loser.\n\nCLICK TO CONFIRM";

    /*=================================================
    CONSTANTLY UPDATES THE COLORS OF THE AUTON SELECTOR
    =================================================*/
    while(!confirmed) {
        switch(autonType) {
            case 0:
                lv_label_set_text(confirmLabel, stack8Desc);
                break;
            case 1:
                lv_label_set_text(confirmLabel, row7Desc);
                break;
            case 2:
                lv_label_set_text(confirmLabel, row6Desc);
                break;
            case 3:
                lv_label_set_text(confirmLabel, stack7Desc);
                break;
            case 10:
                lv_label_set_text(confirmLabel, noneDesc);
                break;
            case 4:
                lv_label_set_text(confirmLabel, skillsDesc);
                break;
        }
        if(autonColor) {
            lv_btn_set_style(color, LV_BTN_STYLE_PR, &blueRed);
            lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_TGL_PR, &blueOutline);
            lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_TGL_REL, &blueOutline);
        }
        else {
            lv_btn_set_style(color, LV_BTN_STYLE_PR, &redBlue);
            lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_TGL_PR, &redOutline);
            lv_btnm_set_style(auton, LV_BTNM_STYLE_BTN_TGL_REL, &redOutline);
        }
        delay(100);
    }

    /*=======================
    COVER AFTER AUTON CONFIRM
    =======================*/
    //imu.reset();
    lv_obj_t *cover = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_pos(cover, 0, 0);
    lv_obj_set_size(cover, 480, 240);
    black.body.radius = 0;
    lv_obj_set_style(cover, &black3);
    lv_obj_t *coverLabel = lv_label_create(cover, NULL);
    lv_label_set_align(coverLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(coverLabel, "GO GET EM BOYS");

}

void disabled() {

    

}