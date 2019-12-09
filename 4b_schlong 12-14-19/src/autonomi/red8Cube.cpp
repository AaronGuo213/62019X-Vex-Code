#include "main.h"

void red8Cube() {

    runIntk(100);
    moveStraight(35, 2300, 60);
    runIntk(0);

    turn(-2.5, 750);
    moveLift(200);
    moveStraight(-32.5, 1100);
    moveLift(0);
    turn(2.5, 750);

    runIntk(100);
    moveStraight(32, 2300, 60);
    runIntk(0);

    turn(-6.65, 1400, 50);
    moveTray(400);
    moveStraight(30, 2000);
    outtake();

    /*//gets the preload and 3 cubes from the long L
    runIntk(100);
    moveStraight(35, 2100, 60);
    moveLift(200);
    moveStraight(-7, 700, 80);
    moveLift(0);

    //stops the intake and moves to set up for the row of 4
    runIntk(0);
    turn(2.5, 750);
    setLiftIdle();
    moveStraight(-32.5, 1050);
    turn(-2.6, 800);

    //intakes the 4 cubes in the row
    runIntk(100);
    moveStraight(32, 2300, 60);

    runIntk(-7);
    moveTray(400);
    moveStraight(-23.5, 1100);
    runIntk(0);
    turn(-6.65, 1400, 50);
    moveStraight(16, 1200, 70);
    outtake();*/

}