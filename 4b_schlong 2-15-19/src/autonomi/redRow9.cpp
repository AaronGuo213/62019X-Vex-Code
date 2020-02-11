#include "main.h"

void redRow9() {

    moveTray(0);
    runIntk(100);
    moveStraight(24, 12, 0, 1300, 100, 50);
    liftStat = LiftStatus::manual;
    moveLift(atCube[2]);
    delay(1000);
    moveLift(0, 500);
    moveStraight(12, 0, 1500, 30);
    setLiftIdle();

    /*curveBasePID(-23.4, -17.25, 1300, 80);
    runIntk(0);
    curveBasePID(-17.25, -23.4, 1400, 80);*/
    runIntk(0);
    curveBasePID(-24, -17.5, 1400, 80);
    curveBasePID(-17.5, -24, 1400, 80);

    setTrayIdle();
    runIntk(100);
    moveStraight(33, 1, 3000, 45);

    //curveBasePID(-8, -18.5, 2500, 80);
    moveStraight(-13, 0, 800);
    runIntk(0);
    runIntkDist(-100, 30);
    turn(-120, 0, 1700, 70);
    runIntk(0);
    trayStat = TrayStatus::manual;
    runTray(100);
    moveStraight(12, 1, 1000, 80);
    //moveStraight(14, 1, 900, 70);
    outtake();

}