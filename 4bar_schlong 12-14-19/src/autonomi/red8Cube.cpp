#include "main.h"

void red8Cube() {

    //gets the preload and 3 cubes from the long L
    runIntk(100);
    moveStraight(42, 1500);
    moveStraight(31, 2500, 60);

    //stops the intake and moves to set up for the row of 4
    runIntk(0);
    turn(20, 1000);
    moveStraight(-50, 1500);
    turn(-20, 1000);

    //intakes the 4 cubes in the row
    runIntk(100);
    moveStraight(60, 4000, 60);

    //moves to the intake and outtakes
    moveStraight(-50, 1500);
    turn(-60, 1000, 80);
    moveStraight(20, 1000);
    outtake(-50);

}