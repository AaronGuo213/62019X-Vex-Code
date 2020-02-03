#include "main.h"

void redRow9() {

    moveTray(0);
    runIntk(100);
    moveLift(150);
    moveLift(0, 500);
    moveStraight(24, 12, 0, 2000, 75, 50);
    moveLift(atCube[2]);
    moveLift(0, 900);
    delay(500);
    moveStraight(11, 0, 1000, 30);
    setLiftIdle();

    curveBasePID(-23.4, -17.25, 1300, 80);
    runIntk(0);
    curveBasePID(-17.25, -23.4, 1400, 80);
    //curveBasePID(-19.7, -24.7, 1300, 80);
    /*curveBaseVel(-41.5, -36.2, 2500, 100);
    turn(-85, 0, 1000);*/

    setTrayIdle();
    runIntk(100);
    moveStraight(33, 0, 2500, 50);

    //curveBasePID(-8, -18.5, 2500, 80);
    moveStraight(-15, 1, 1500);
    runIntk(0);
    runIntkDist(-100, 50);
    turn(-126, 0, 1400, 60);
    runIntk(0);
    moveTray(300);
    moveStraight(14, 1, 1200, 60);
    //moveStraight(14, 1, 900, 70);
    outtake();

}