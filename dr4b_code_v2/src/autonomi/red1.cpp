#include "main.h"

void red1() { //autonomous that stacks 6 cubes in the large goal

    liftSetPoint = 700; //stacks first cube
    moveStraight(45, 1800, 70);
    liftSetPoint = 300;
    delay(500);

    liftSetPoint = 1400; //stakcs 4 more cubes
    delay(1000);
    moveStraight(29, 2000, 30);
    liftSetPoint = 700;
    delay(1000);
    liftSetPoint = 800;
    delay(500);

    moveStraight(-15, 1000, 30);
    liftSetPoint = 500;
    delay(1000);
    moveStraight(-50, 1500, 60); //moves back and turns to face the goal
    turn(90, 1000, 80);
    moveStraight(60, 1700, 80); //moves to goal and outtakes
    liftSetPoint = 300;
    moveStraight(12, 1200, 40);
    setIntk(0);
    delay(500);
    moveStraight(-20, 1000, 60);

}