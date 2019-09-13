#include "main.h"

void setIntk(bool status) {

    intk.set_value(status);

}

bool powerRollers = false;

void setRollers(bool status) {

    rollers.set_value(status);
    powerRollers = status;

}

void runRollers(float percent) {

    leftRoller.move_voltage(120 * percent);
    rightRoller.move_voltage(120 * percent);

}

void rollerCtrl(void* param) {

    while(true) {

        runRollers(powerRollers * 70);

        delay(10);

    }

}