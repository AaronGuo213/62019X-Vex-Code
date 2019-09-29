#include "main.h"

void blue3() { //autonomous for the four in a row

    liftSetPoint = 600; //stacks the first cube
    moveStraight(37, 1500);
    stack = true;
    delay(800);

    moveStraight(12, 700, 40); //stacks the second cube
    stack = true;
    delay(800);

    moveStraight(12, 700, 40); //stacks the third cube
    stack = true;
    delay(800);

    moveStraight(12, 700, 40); //stacks the fourth cube
    stack = true;
    delay(800);

    liftSetPoint = 500; //lifts the cubes above the ground
    delay(500); //this helps the robot avoid dragging
    moveStraight(-30, 1700, 30); //moves back and turns to the goal
    turn(128, 1400, 40);
    moveStraight(60, 2000, 70); //runs into the goal
    liftSetPoint = 300; //outtakes and moves back from the stack
    delay(500);
    setIntk(0);
    delay(500);
    moveStraight(-50, 1000, 50);

}