#include "main.h"

void runLeftBase(double percent) {

    leftBase1.move_voltage(percent * 120);
    leftBase2.move_voltage(percent * 120);

}

void runRightBase(double percent) {

    rightBase1.move_voltage(percent * 120);
    rightBase2.move_voltage(percent * 120);

}