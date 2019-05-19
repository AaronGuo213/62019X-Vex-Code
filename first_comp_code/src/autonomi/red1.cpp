#include "main.h"

void red1() {

    setPoint = 0;
    moveStraight(0, 90, 0);
    turn(45, 0);
    moveStraight(0, 90, 0);
    runClaw(-100);
    delay(300);
    runClaw(0);

    setPoint = 0;
    moveStraight(0, 225, 0);
    turn(45, 0);
    setPoint = 0;
    moveStraight(0, 90, 0);
    runClaw(100);
    delay(300);

    moveStraight(0, 200, 0);
    setPoint = 0;
    turn(180, 0);
    moveStraight(0, 90, 0);
    setPoint = 0;
    runClaw(-100);
    delay(300);
    
    setPoint = 0;
    moveStraight(0, 180, 0);
    reset = true;
    turn(180, 0);

}