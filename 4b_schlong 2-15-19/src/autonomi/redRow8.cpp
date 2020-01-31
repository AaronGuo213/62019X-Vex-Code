#include "main.h"

void redRow8() {

    Odometry *tracker = new Odometry(0, 0, 0);
    Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

    moveLift(100, 100);
    moveStraight(12, 1, 900, 60);
    setLiftIdle();
    moveTray(0);
    runIntk(100);
    moveStraight(23, 0, 2300, 50);
    runIntk(0);

    curveBasePID(-23.4, -17.25, 1300, 80);
    curveBasePID(-17.25, -23.4, 1400, 80);
    //curveBasePID(-19.7, -24.7, 1300, 80);
    /*curveBaseVel(-41.5, -36.2, 2500, 100);
    turn(-85, 0, 1000);*/

    setTrayIdle();
    runIntk(100);
    moveStraight(33, 0, 3000, 40);
    runIntk(0);

    //curveBasePID(-8, -18.5, 2500, 80);
    moveStraight(-15, 1, 1500);
    runIntkDist(-100, 50);
    turn(-126, 0, 1400, 60);
    runIntk(0);
    moveTray(300);
    moveStraight(14, 1, 900, 70);
    outtake();

}