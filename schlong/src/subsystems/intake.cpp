#include "main.h"

void runIntk(double percent) {

    intk1.move_voltage(percent * 100);
    intk2.move_voltage(percent * 100);

}

void runTray(double percent) {

    tray.move_voltage(percent * 120);

}