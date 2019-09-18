#include "main.h"

void red1() { //autonomous that stacks 6 cubes in the large goal

    setIntk(1); //grabs onto preload

    liftSetPoint = 100; //stacks first cube
    moveStraight(25, 1000);
    liftSetPoint = 0;
    delay(500);

    moveStraight(35, 3000); //moves to 4 stack
    liftSetPoint = 400; //stakcs 4 more cubes
    moveStraight(12, 2000, 60);
    liftSetPoint = 0;
    delay(2000);
    liftSetPoint = 50;

    moveStraight(-65, 4000); //moves back and turns to face the goal
    turn(100, 1000);
    moveStraight(15, 1000); //hits wall at an angle

    runRightBase(-60); //alligns with wall
    delay(300);

    moveStraight(15, 1000); //moves to goal and outtakes
    liftSetPoint = 0;
    delay(200);
    setIntk(0);
    moveStraight(-10, 500);

}