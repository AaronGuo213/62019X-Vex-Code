#include "main.h"

void runIntk(double percent) {

    intk1.move_voltage(percent * 120);
    intk2.move_voltage(percent * 120);

}

void runTray(double percent) {

    tray.move_voltage(percent * 120);

}