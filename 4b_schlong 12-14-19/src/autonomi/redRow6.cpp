#include "main.h"

void redRow6() {

    runIntk(100);
    moveTray(0);
    moveStraight(6, 1000);
    moveLift(300);
    delay(500);
    moveLift(0);
    delay(500);
    moveStraightTimed(33, 2300, 70);
    setLiftIdle();
    tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    trayStat = TrayStatus::idle;
    
    turn(1, 500);
    moveStraightTimed(10, 1200);
    runIntk(0);

    moveStraight(-30, 2000);
    turnTimed(-7, 2200, 40);

    leftIntk.move_relative(-180, 50);
    rightIntk.move_relative(-180, 50);
    moveStraight(10, 1000);
    outtake();

}