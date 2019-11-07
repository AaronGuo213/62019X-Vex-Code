#include "main.h"

void skills() {

    moveLift(onTower[1]);
    delay(400);
    moveToObject(30);
    delay(500);
    setIntk(0);
    moveStraight(-18, 1000, 40);
    moveLift(0);
    delay(800);
    setIntk(1);

    turn(-27, 1000, 100);
    moveStraight(-33, 1500, 70);
    turn(47, 1500);
    runLeftBase(-30);
    runRightBase(-30);
    delay(1000);

    /*red1();

    moveStraight(-15, 2000, 40);
    moveLift(onCubes[0]);
    moveStraight(-50, 2000);
    turn(-60, 1500);
    moveLift(onCubes[1]);
    moveStraight(80, 2500);
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(-5, 500, 60);
    moveLift(onTower[2]);
    delay(1500);
    moveStraight(15, 1000, 60);
    setLock(0);
    moveLift(onCubes[6]);*/

}