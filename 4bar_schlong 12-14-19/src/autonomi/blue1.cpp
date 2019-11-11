#include "main.h"

void blue1() { //autonomous for the four stack

    moveLift(onCubes[1]); //stacks first cube
    delay(100);
    moveStraight(52, 1400, 70);
    liftToGnd(20);

    moveLift(onCubes[4]); //stakcs 4 more cubes
    delay(1000);
    moveToObject(25);
    delay(200);
    liftToGnd(30);
    delay(100);
    moveLift(onCubes[0]); //lifts the cubes off the ground
    delay(500);

    moveStraight(-65, 1700, 80); //moves back and turns to face the goal
    turn(-58, 1200, 60);
    moveStraight(60, 1500, 80); //moves to goal
    moveStraight(11, 1200, 40);

    liftToGnd(5); //lowers cubes and outtakes
    delay(200);
    setLock(0);
    delay(200);
    moveLift(onCubes[6]);
    delay(1300);
    moveStraight(-6, 500, 20);

}