#include "main.h"

void red1() { //autonomous that stacks 6 cubes in the large goal

    liftSetPoint = 600; //stacks first cube
    moveStraight(55, 2000);
    liftSetPoint = 300;
    delay(700);

    liftSetPoint = 1300; //stakcs 4 more cubes
    delay(1500);
    moveStraight(15, 1500, 45);
    setIntk(0);
    delay(100);
    moveStraight(-10, 1000, 45);
    liftSetPoint = 600;
    delay(2000);
    moveStraight(12, 1500, 45);
    setIntk(1);
    delay(100);

    moveStraight(-60, 4000); //moves back and turns to face the goal
    turn(90, 1500);
    moveStraight(72, 4000); //moves to goal and outtakes
    liftSetPoint = 300;
    delay(200);
    setIntk(0);
    moveStraight(-10, 1000);

}