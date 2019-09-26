#include "main.h"

void red1() { //autonomous that stacks 6 cubes in the large goal

    liftSetPoint = 700; //stacks first cube
    moveStraight(45, 2000, 70);
    liftSetPoint = 300;
    delay(700);

    liftSetPoint = 1400; //stakcs 4 more cubes
    delay(1500);
    moveStraight(25, 2000, 30);
    setIntk(0);
    delay(500);
    moveStraight(-15, 2000, 30);
    liftSetPoint = 600;
    delay(2000);
    moveStraight(15, 2000, 20);
    setIntk(1);
    delay(1000);

    moveStraight(-65, 2500, 80); //moves back and turns to face the goal
    turn(90, 1500, 60);
    moveStraight(60, 2000, 80); //moves to goal and outtakes
    moveStraight(5, 1000, 40);
    liftSetPoint = 300;
    moveStraight(5, 1000, 40);
    delay(500);
    setIntk(0);
    delay(500);
    moveStraight(-10, 1000);

}