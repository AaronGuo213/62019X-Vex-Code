#include "main.h"

void redRow8() {

    //deploys antitip
    moveLift(150, 100);
    moveStraight(12, 1, 900, 60);
    setLiftIdle();
    moveTray(0);

    //gets 3 cubes from the long L
    runIntk(100);
    moveStraight(23, 0, 2300, 50);
    runIntk(0);

    //S path to the row of 4
    curveBasePID(-23.4, -17.25, 1300, 80);
    curveBasePID(-17.25, -23.4, 1400, 80);

    //gets the row of 4
    setTrayIdle();
    runIntk(100);
    moveStraight(33, 0, 2500, 60);
    runIntk(0);

    //outtakes
    moveStraight(-15, 1, 1500);
    runIntkDist(-100, 50);
    turn(-126, 0, 1400, 60);
    runIntk(0);
    moveTray(200);
    moveStraight(14, 1, 1200, 60);
    outtake();

}