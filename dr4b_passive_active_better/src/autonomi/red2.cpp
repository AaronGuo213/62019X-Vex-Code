#include "main.h"

void red2() { //autonomous for the long L

    moveLift(onCubes[1]); //stacks the first cube
    moveStraight(47, 2000, 80);
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(12.8, 1000, 30); //stacks the second cube
    liftStat = LiftStatus::stack;
    delay(1000);

    moveLift(onCubes[2]); //moves the lift above the two cubes
    delay(1500);
    moveStraight(14, 1000, 30);
    liftStat = LiftStatus::uncontrolled;
    runLift(-100);
    while(getLiftHeight() > 30) //stacks the last two cubes
        delay(10);
    runLift(0);

}