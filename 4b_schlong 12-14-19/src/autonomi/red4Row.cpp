#include "main.h"

void red4Row() {

    //gets the preload and the 4 cubes in the row
    runIntk(100);
    moveStraight(70, 4000, 50);

    //moves to the goal and outtakes
    moveStraight(-50, 2000);
    turn(-60, 1500, 80);
    moveStraight(20, 1000, 70);
    outtake(-50);

}