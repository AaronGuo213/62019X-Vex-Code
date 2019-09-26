#include "main.h"

void red3() {

    liftSetPoint = 600;
    moveStraight(37, 1500);
    stack = true;
    delay(800);
    moveStraight(12, 700, 40);
    stack = true;
    delay(800);
    moveStraight(12, 700, 40);
    stack = true;
    delay(800);
    moveStraight(12, 700, 40);
    stack = true;
    delay(800);
    liftSetPoint = 500;
    delay(500);
    moveStraight(-40, 2000, 5);
    turn(-128, 1000, 40);
    moveStraight(60, 2000, 70);
    liftSetPoint = 300;
    delay(500);
    setIntk(0);
    delay(500);
    moveStraight(-50, 1000, 50);

}