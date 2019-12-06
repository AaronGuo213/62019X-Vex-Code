#include "main.h"

void red8Cube() {

    //gets the preload and 3 cubes from the long L
    runIntk(100);
    moveStraight(32, 2500, 70);

    //stops the intake and moves to set up for the row of 4
    runIntk(0);
    turn(1.5, 1000);
    moveStraight(-32, 2500);
    turn(-3, 1000);
    moveStraight(-5, 1000);

    //intakes the 4 cubes in the row
    /*runIntk(100);
    moveStraight(30, 4000, 60);

    //moves to the intake and outtakes
    moveStraight(-25, 1500);
    turn(-6, 1000, 80);
    moveStraight(10, 1000);
    outtake(-50);*/

}