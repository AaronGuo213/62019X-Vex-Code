#include "main.h"

void redRow8() {

    Odometry *tracker = new Odometry(0, 0, 0);
    Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

    runIntk(100);
    moveStraight(35, 0, 2500, 70);
    runIntk(0);

    curveBasePID(-24, -19, 1300, 80);
    curveBasePID(-19.7, -24.7, 1300, 80);

    moveLift(300);
    moveStraight(4, 0, 1000);
    setLiftIdle();
    delay(500);

    runIntk(100);
    moveStraight(29, 0, 3000, 40);
    runIntk(0);

    curveBasePID(-8, -18.5, 2000, 80);
    runIntkDist(-180, 50);
    moveTray(400);
    moveStraight(16, 0, 2500);
    /*outtake();*/

}