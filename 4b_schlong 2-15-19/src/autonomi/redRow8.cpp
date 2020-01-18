#include "main.h"

void redRow8() {

    Odometry *tracker = new Odometry(0, 0, 0);
    Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

    runIntk(100);
    moveStraight(39, 0, 2500, 70);
    runIntk(0);

    curveBase(-100, -15, 19);
    curveBase(-15, -100, 21);
    moveStraight(-2, 0, 500);

    moveLift(300);
    delay(500);
    moveLift(0);
    delay(500);

    runIntk(100);
    moveStraight(33, 0, 2500, 70);

    curveBase(-80, -80, 20);
    curveBase(-15, -100, 25);
    moveStraight(-2, 0, 500);
    turnToAngle(tracker, -135);
    runIntkDist(-180, 50);
    moveStraight(30, 1, 2500);
    outtake();

}