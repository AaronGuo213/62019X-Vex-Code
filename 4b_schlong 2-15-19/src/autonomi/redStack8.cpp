#include "main.h"

void redStack8() {

    //gets the first cube
    runIntk(100);
    moveTray(0);
    moveStraight(22, 0, 1300, 70);
    runIntk(0);
    moveLift(atCube[4]);
    delay(1700);
    runIntk(100);
    moveStraight(4, 0, 1000, 30);
    liftStat = LiftStatus::manual;
    lift.move_velocity(-50);
    while(getLiftHeight() > 70)
        delay(10);
    setLiftIdle();
    setTrayIdle();
    curveBaseVel(20.5, 21, 1500, 60);
    turn(110, 0, 1400, 60);
    moveStraight(38, 30, 1, 2000, 100, 50);
    moveTray(400);
    runIntkDist(-130, 50);
    moveStraight(-2, 0, 1000, 60);
    outtake();

    //gets the cubes from the 4 stack
    /*moveStraight(5.5, 700, 40);
    runIntk(100);
    liftStat = LiftStatus::manual;
    lift.move_velocity(-50);
    while(getLiftHeight() > 50)
        delay(10);
    liftStat = LiftStatus::idle;

    //gets the cube next to the tower
    curveBase(30, 100, 15);
    moveStraight(2, 0, 500);
    delay(500);
    runIntk(0);

    //gets the stray cube near the goal
    turn(90, 1, 1500);
    runIntk(100);
    moveStraight(35, 0, 1600, 80);

    //moves to the goal and outtakes
    runIntkDist(-150, 50);
    curveBase(40, 100, 10);
    moveStraight(2, 0, 500);
    outtake();*/

}