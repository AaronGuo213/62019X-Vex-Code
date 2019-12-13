#include "main.h"

void redRow6() {

    runIntk(100);
    moveTray(0);
    moveStraightTimed(39, 2300, 70);
    tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    trayStat = TrayStatus::idle;
    
    turn(1, 500);
    moveStraightTimed(10, 1200);
    runIntk(0);

    moveLift(300);
    moveStraight(-30, 2000);
    setLiftIdle();
    turnTimed(-7, 2200, 40);

    leftIntk.move_relative(-180, 50);
    rightIntk.move_relative(-180, 50);
    moveStraight(10, 1000);
    moveStraight(-2, 500);
    outtake();

}