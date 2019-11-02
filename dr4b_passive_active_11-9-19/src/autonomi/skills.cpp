#include "main.h"

void skills() {

    moveLift(onTower[1]);
    delay(1000);
    moveStraight(15, 1500, 60);
    setLock(0);
    delay(200);
    setLock(1);
    moveStraight(-10, 1000, 60);
    moveLift(onCubes[0]);

    turn(-20, 1000, 100);
    moveStraight(-15, 1500);
    turn(60, 1500);
    moveStraight(-6, 1000, 60);

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