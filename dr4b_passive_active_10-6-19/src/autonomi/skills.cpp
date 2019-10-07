#include "main.h"

void skills() {

    liftSetPoint = 700; //stacks first cube
    moveStraight(45, 1800, 70);
    liftSetPoint = 300;
    delay(500);

    liftSetPoint = 1400; //stakcs 3 more cubes
    delay(1000);
    moveStraight(29, 2000, 30);
    liftSetPoint = 700;
    delay(1000);

    liftSetPoint = 800; //moves back and moves the lift down for stability
    delay(500);
    moveStraight(-15, 1000, 30);
    liftSetPoint = 500;
    delay(1000);

    moveStraight(-40, 1500, 60); //moves back and turns to face the goal
    turn(90, 1000, 80);
    liftSetPoint = 700;

    moveStraight(15, 1000, 60);
    liftSetPoint = 300;
    delay(500);
    moveStraight(-5, 1000, 20);
    liftSetPoint = 800;
    moveStraight(10, 1000, 60);
    setLock(0);
    delay(300);
    setLock(1);
    moveStraight(-10, 1500, 20);
    liftSetPoint = 500;
    delay(1000);
    turn(170, 2000, 60);
    moveStraight(60, 1700, 80);
    moveStraight(12, 1200, 40);
    liftSetPoint = 300;
    delay(500);
    setIntk(0);
    delay(500);
    moveStraight(-10, 1000, 70);

}