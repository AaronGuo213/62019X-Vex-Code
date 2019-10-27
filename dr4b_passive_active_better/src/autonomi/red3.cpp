#include "main.h"

void red3() { //autonomous for the four in a row

    moveLift(onCubes[1]); //stacks the first cube
    moveStraight(32, 1500, 80);
    moveStraight(5, 1000, 40);
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(12, 1000, 30); //stacks the second cube
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(12, 1200, 30); //stacks the third cube
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(12, 1000, 30); //stacks the fourth cube
    liftStat = LiftStatus::stack;
    delay(1000);

    moveLift(onCubes[0]); //lifts the cubes above the ground
    delay(500); //this helps the robot avoid dragging
    moveStraight(-39, 2000, 30); //moves back and turns to the goal
    turn(-110, 1400, 40);
    moveStraight(60, 2000, 70); //runs into the goal
    moveLift(0); //outtakes and moves back from the stack
    delay(500);
    setIntk(0);
    delay(500);
    moveStraight(-50, 1000, 50);
    
}