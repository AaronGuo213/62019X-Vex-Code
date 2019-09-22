#include "main.h"

void red3() {

    liftSetPoint = 600;
    moveStraight(37, 1500);
    liftSetPoint = 300;
    delay(700);
    liftSetPoint = 700;
    delay(700);
    moveStraight(11, 1000, 60);
    liftSetPoint = 300;
    delay(700);
    liftSetPoint = 700;
    delay(700);
    moveStraight(11, 1000, 60);
    liftSetPoint = 300;
    delay(700);
    liftSetPoint = 700;
    delay(700);
    moveStraight(11, 1000, 60);
    liftSetPoint = 300;
    delay(700);
    liftSetPoint = 400;
    delay(700);
    /*moveStraight(-65, 3000);
    turn(-90, 1500);
    moveStraight(30, 1000);
    setIntk(0);*/

}