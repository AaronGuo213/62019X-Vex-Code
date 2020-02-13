#include "main.h"

void runIntk(double percent) {

    intk1.move_voltage(percent * 100);
    intk2.move_voltage(percent * 100);

}

void runTray(double percent) {

    tray.move_voltage(percent * 120);

}

double getTrayPow() {

    return (1800 - tray.get_position()) / 10;

}