#include "main.h"

void runIntk(double percent) {

    intk1.move_voltage(percent * 100);
    intk2.move_voltage(percent * 100);

}

void runTray(double percent) {

    tray.move_voltage(percent * 120);

}

void runArms(double percent) {

    arms.move_voltage(percent * 120);

}

double getTrayPow(bool isOuttaking) {

    if(isOuttaking)
        return (2200 - tray.get_position()) / 10;

    return -tray.get_position();

}