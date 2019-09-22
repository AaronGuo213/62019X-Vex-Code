#include "main.h"

void red2() {

    liftSetPoint = 600;
    moveStraight(23, 1000);
    liftSetPoint = 300;
    delay(500);
    liftSetPoint = 600;
    delay(500);
    moveStraight(13, 1000, 50);
    turn(-95, 1500);
    moveStraight(36, 2000, 70);
    liftSetPoint = 300;
    delay(500);
    liftSetPoint = 500;
    delay(500);
    turn(-130, 2000);


}