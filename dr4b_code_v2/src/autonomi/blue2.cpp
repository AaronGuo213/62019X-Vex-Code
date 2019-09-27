#include "main.h"

void blue2() { //autonomous for the long L

    liftSetPoint = 600;
    moveStraight(48, 1500);
    stack = true;
    delay(800);
    moveStraight(12, 1000, 25);
    stack = true;
    delay(800);
    liftSetPoint = 900;
    delay(1000);
    moveStraight(13, 1000, 30);
    liftSetPoint = 300;

}