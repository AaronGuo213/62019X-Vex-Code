#include "main.h"

void blueRow9() {

    //gets the first 2 cubes
    moveTray(0);
    runIntk(100);
    moveStraight(24, 12, 0, 1300, 100, 50);

    //deploys antitip and gets the stack of 2
    liftStat = LiftStatus::manual;
    moveLift(atCube[2]);
    delay(1000);
    moveLift(0, 500);
    moveStraight(12, 0, 1500, 30);
    setLiftIdle();

    //S-shaped path to line up with the row of 4
    runIntk(0);
    curveBasePID(-17.5, -24, 1400, 80);
    curveBasePID(-24, -17.5, 1400, 80);

    //gets the row of 4
    setTrayIdle();
    runIntk(100);
    moveStraight(33, 1, 3000, 45);

    //backs up and turns to the goal while positioning cubes for outtaking
    moveStraight(-13, 0, 800);
    runIntk(0);
    runIntkDist(-100, 30);
    turn(120, 0, 1700, 70);

    //preemtively puts up tray while moving to the goal
    runIntk(0);
    trayStat = TrayStatus::manual;
    runTray(100);
    moveStraight(12, 1, 1000, 80);
    outtake();

}