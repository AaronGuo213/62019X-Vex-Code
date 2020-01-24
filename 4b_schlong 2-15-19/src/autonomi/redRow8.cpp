#include "main.h"

void redRow8() {

    Odometry *tracker = new Odometry(0, 0, 0);
    Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

    moveLift(400);
    moveStraight(12, 0, 1000);
    setLiftIdle();
    runIntk(100);
    moveStraight(23, 0, 2500, 40);
    runIntk(0);

    /*curveBasePID(-24, -19, 1300, 80);
    curveBasePID(-19.7, -24.7, 1300, 80);*/
    curveBasePID(20, 17, 1300, 100);
    turn(-90, 1, 1500);

    runIntk(100);
    moveStraight(33, 0, 3000, 40);
    runIntk(0);

    //curveBasePID(-8, -18.5, 2500, 80);
    turn(-135, 0, 2000, 60);
    runIntkDist(-100, 50);
    moveStraight(20, 0, 2500);
    /*outtake();*/

}