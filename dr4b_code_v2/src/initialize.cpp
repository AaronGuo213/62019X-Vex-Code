#include "main.h"

void initialize() {

    Task liftGo (liftCtrl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "lift control task"); //starts lift slow and hold tasks
    delay(100);
    liftSetPoint = getLiftHeight();

}

int autonCount = 0;

void lcdScroll() {

    if(autonCount > 3) { //loops the options

        autonCount = 0;

    }

    else if(autonCount < 0) { //loops the options

        autonCount = 3;

    }

    switch(autonCount) {

        case 0:
            lcd::set_text(1, "RED1");
            break;

        case 1:
            lcd::set_text(1, "RED2");
            break;

        case 2:
            lcd::set_text(1, "BLUE1");
            break;

        case 3:
            lcd::set_text(1, "BLUE2");
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

}

void competition_initialize() {

    lcd::initialize();
    lcd::set_text(0, "choose auton");
    lcdScroll();
    lcd::register_btn0_cb(on_left_pressed);
    lcd::register_btn1_cb(on_center_pressed);
    lcd::register_btn2_cb(on_right_pressed);

}

void disabled() {



}