#include "main.h"

void red4Stack() {

    //gets the first cube
    runIntk(100);
    moveStraight(52, 1400);

    //gets the cubes from the 4 stack
    moveLift(atCube[5]);
    delay(2000);
    moveStraight(20, 1000, 60);
    moveLift(atCube[0]);
    delay(2000);
    setLiftIdle();

    //gets the cube next to the tower
    turn(10, 1000);
    moveStraight(30, 1500);

    //gets the stray cube near the goal
    turn(60, 1500);
    moveStraight(50, 2000);

    //outtakes
    turn(-10, 1000);
    moveStraight(20, 1000, 80);
    outtake(-50);

}