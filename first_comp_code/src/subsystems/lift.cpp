#include "main.h"

void runLift(float percentage) {

    lift1.move_voltage(percentage * 120);
    lift2.move_voltage(percentage * 120);

}