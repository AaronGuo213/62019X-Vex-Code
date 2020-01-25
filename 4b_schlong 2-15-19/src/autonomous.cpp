#include "main.h"

void autonomous() { //15 second autonomous period at the beginning of the match

    //redRow8();
    //turn(90, 0, 1500);
    Odometry *tracker = new Odometry(0, 0, 90);
    Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");
    moveToPointForwards(tracker, 12, 12);

}