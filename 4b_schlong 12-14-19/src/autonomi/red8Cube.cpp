#include "main.h"

void red8Cube() {

    //gets the preload and 3 cubes from the long L
    runIntk(100);
    moveStraight(30, 2500, 60);
    moveStraight(-7, 700, 80);

    //stops the intake and moves to set up for the row of 4
    runIntk(0);
    turn(2.5, 1000);
    moveStraight(-32.5, 1300);
    turn(-2.5, 1200);

    //intakes the 4 cubes in the row
    runIntk(100);
    moveStraight(32, 2500, 60);

    runIntk(0);
    turn(1.2, 1000);
    runIntk(100);
    moveStraight(8, 700, 60);

    moveStraight(-20, 1500);
    runIntk(0);
    turn(-6.2, 2000, 70);

    //moves to the intake and outtakes
    runIntk(-15);
    moveStraight(8, 1000);
    runIntk(0);
    outtake(0);

}