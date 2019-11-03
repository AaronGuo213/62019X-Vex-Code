#include "main.h"

void blue2() { //autonomous for the long L

    moveLift(onCubes[1]); //stacks the first cube
    moveStraight(47, 2000, 80);
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(13, 1000, 30); //stacks the second cube
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(14, 1000, 30); //pushes the top cube off and gets the lower cube
    liftToGnd(30);

}