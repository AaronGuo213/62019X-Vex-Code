#include "main.h"

void redRow9() {

    moveTray(0);
    runIntk(100);
    moveLift(150);
    moveLift(0, 500);
    moveStraight(24, 12, 0, 1300, 75, 50);
    liftStat = LiftStatus::manual;
    moveLift(atCube[2]);
    delay(1000);
    moveLift(0, 500);
    moveStraight(12, 0, 1500, 25);
    setLiftIdle();

    /*curveBasePIDCut(-46.8, -34.5, 22, 80);
    runIntk(0);
    curveBasePID(-16.75, -22.5, 1300, 80);*/
    curveBasePID(-23.4, -17.25, 1300, 80);
    runIntk(0);
    curveBasePID(-17.25, -23.4, 1400, 80);

    setTrayIdle();
    runIntk(100);
    moveStraight(33, 1, 3000, 45);

    //curveBasePID(-8, -18.5, 2500, 80);
    moveStraight(-13, 0, 800);
    runIntk(0);
    runIntkDist(-100, 50);
    turn(-120, 0, 1400, 60);
    runIntk(0);
    //moveTray(300);
    trayStat = TrayStatus::manual;
    runTray(90);
    moveStraight(14, 1, 1000, 80);
    //moveStraight(14, 1, 900, 70);
    outtake();

}