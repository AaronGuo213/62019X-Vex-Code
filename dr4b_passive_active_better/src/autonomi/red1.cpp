#include "main.h"

void red1() { //autonomous for the four stack

    moveLift(onCubes[1]); //stacks first cube
    delay(100);
    moveStraight(45, 1500, 70);
    liftStat = LiftStatus::uncontrolled;
    runLift(-100);
    while(getLiftHeight() > 20)
        delay(10);
    runLift(0);

    moveLift(onCubes[4]); //stakcs 3 more cubes
    delay(1000);
    moveStraight(24, 2500, 30);
    liftStat = LiftStatus::uncontrolled;
    runLift(-100);
    while(getLiftHeight() > 40) {
        if(leftLift.is_stopped() || rightLift.is_stopped())
            delay(15000);
        delay(10);
    }
    runLift(0);
    delay(100);
    moveLift(20);
    delay(500);

    moveStraight(-65, 1900, 80); //moves back and turns to face the goal
    turn(58, 1500, 60);
    moveStraight(60, 1500, 80); //moves to goal and lowers lift to the ground
    moveStraight(12, 1200, 40);

    liftStat = LiftStatus::uncontrolled;
    runLift(-100);
    while(getLiftHeight() > 5)
        delay(10);
    runLift(0);
    delay(200);
    setLock(0); //outtakes
    delay(200);
    moveLift(onCubes[6]);

}