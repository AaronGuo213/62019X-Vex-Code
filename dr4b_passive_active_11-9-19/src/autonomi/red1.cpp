#include "main.h"

void red1() { //autonomous for the four stack

    moveLift(onCubes[1]); //stacks first cube
    delay(100);
    moveStraight(52, 1400, 70);
    liftStat = LiftStatus::manual;
    runLift(-100);
    while(getLiftHeight() > 20)
        delay(10);
    runLift(0);

    moveLift(onCubes[4]); //stakcs 3 more cubes
    delay(1000);
    //moveStraight(24, 2500, 30);
    runLeftBase(25);
    runRightBase(25);
    while(!cubeTrigger.get_value())
        delay(10);
    runLeftBase(0);
    runRightBase(0);
    delay(200);

    liftStat = LiftStatus::manual;
    runLift(-100);
    while(getLiftHeight() > 30)
        delay(10);
    runLift(0);
    delay(100);
    moveLift(onCubes[0]);
    delay(500);

    moveStraight(-65, 1700, 80); //moves back and turns to face the goal
    turn(58, 1200, 60);
    moveStraight(60, 1500, 80); //moves to goal and lowers lift to the ground
    moveStraight(14, 1200, 40);

    liftStat = LiftStatus::manual;
    runLift(-100);
    while(getLiftHeight() > 5)
        delay(10);
    runLift(0);
    delay(200);
    setLock(0); //outtakes
    delay(200);
    moveLift(onCubes[6]);
    delay(1300);
    moveStraight(-6, 500, 20);

}