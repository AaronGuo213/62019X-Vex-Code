#include "main.h"

void blueRow8() {

    Odometry *tracker = new Odometry(0, 0, 0);
    Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

    runIntk(100);
    moveStraight(39, 0, 2500, 70);
    runIntk(0);

    curveBasePID(-15, -20, 1500, 80);
    curveBasePID(-20, -15, 1500, 80);

    moveLift(300);
    delay(500);
    moveLift(0);
    delay(500);

    runIntk(100);
    moveStraight(33, 0, 2500, 70);

    moveStraight(-20, 1, 1500);
    curveBasePID(-30, -10, 2000, 80);
    moveStraight(-2, 0, 500);
    turnToAngle(tracker, -135);
    runIntkDist(-180, 50);
    moveTray(400);
    moveStraight(30, 1, 2500);
    outtake();

}