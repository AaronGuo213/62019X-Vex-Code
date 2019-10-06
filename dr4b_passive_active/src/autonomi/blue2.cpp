#include "main.h"

void blue2() { //autonomous for the long L

    liftSetPoint = 650; //stacks the first cube
    moveStraight(48, 1500);
    stack = true;
    delay(800);

    moveStraight(12, 1000, 25); //stacks the second cube
    stack = true;
    delay(800);

    liftSetPoint = 900; //moves the lift above the two cubes
    delay(1000);
    moveStraight(13, 1000, 30);
    liftSetPoint = 300; //stacks the last two cubes

}