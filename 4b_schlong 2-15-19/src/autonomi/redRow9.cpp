#include "main.h"

void redRow9() {

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
    runIntk(0);

    turn(42, 0, 900, 70);
    moveStraight(-34, 0, 1200, 100);
    turn(-43, 0, 900, 70);

    //S-shaped path to line up with the row of 4
    /*runIntk(0);
    curveBasePID(-24, -17.5, 1400, 80);
    curveBasePID(-17.5, -24, 1400, 80);*/

    //gets the row of 4
    setTrayIdle();
    runIntk(100);
    moveStraight(30, 1, 3000, 45);

    //backs up and turns to the goal while positioning cubes for outtaking
    moveStraight(-13, 0, 900);
    runIntk(0);
    turn(-120, 0, 1700, 70);

    //preemtively puts up tray while moving to the goal
    runIntkDist(-150, 200);
    trayStat = TrayStatus::manual;
    runTray(100);
    moveStraight(11, 1, 1000, 80);
    outtake();

}