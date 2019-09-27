#include "main.h"

void blue3() { //autonomous for the four in a row

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
    moveStraight(-30, 1700, 30);
    turn(128, 1400, 40);
    moveStraight(60, 2000, 70);
    liftSetPoint = 300;
    delay(500);
    setIntk(0);
    delay(500);
    moveStraight(-50, 1000, 50);

}