#include "main.h"

void redStack8() {

    //gets the first cube
    runIntk(100);
    moveTray(0);
    moveStraight(22, 0, 1300, 70);
    runIntk(0);

    //gets the 4 stack
    moveLift(atCube[4]);
    delay(1300);
    runIntk(100);
    moveStraight(4, 0, 1800, 30);
    liftStat = LiftStatus::manual;
    lift.move_velocity(-50);
    while(getLiftHeight() > 70)
        delay(10);
    setLiftIdle();
    setTrayIdle();

    //gets the bottom of the 4 stack and the cube at the tower
    curveBaseVel(20.5, 21, 1800, 60);

    //gets the cube next to the goal and outtakes
    turn(110, 0, 1400, 60);
    runIntk(100, 1500);
    moveStraight(36, 30, 1, 2000, 80, 40);
    moveTray(400);
    runIntkDist(-150, 50);
    moveStraight(-1, 0, 1000, 60);
    outtake();

}