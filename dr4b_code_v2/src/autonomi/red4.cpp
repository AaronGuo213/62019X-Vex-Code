#include "main.h"

void red4() {

    liftSetPoint = 600;
    moveStraight(48, 1500);
    stack = true;
    delay(800);
    moveStraight(12, 700, 40);
    stack = true;
    delay(800);
    liftSetPoint = 900;
    delay(1000);
    moveStraight(12, 1000, 30);
    stack = true;

}