#include "main.h"

void redRow9() {

    moveTray(0);
    runIntk(100);
    moveLift(150);
    moveLift(0, 500);
    moveStraight(24, 12, 0, 1600, 75, 50);
    moveLift(atCube[2]);
    delay(500);
    moveLift(0, 400);
    moveStraight(11, 0, 1300, 30);
    setLiftIdle();

    curveBasePIDCut(-46.8, -34.5, 22, 80);
    runIntk(0);
    curveBasePID(-16.75, -22.5, 1400, 80);

    setTrayIdle();
    runIntk(100);
    moveStraight(33, 0, 2500, 50);

    //curveBasePID(-8, -18.5, 2500, 80);
    moveStraight(-15, 1, 1500);
    runIntk(0);
    runIntkDist(-100, 50);
    turn(-123, 0, 1400, 60);
    runIntk(0);
    moveTray(400);
    moveStraight(14, 1, 1200, 60);
    //moveStraight(14, 1, 900, 70);
    outtake();

}