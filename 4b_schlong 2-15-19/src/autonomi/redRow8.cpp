#include "main.h"

void redRow8() {

    runIntk(100);
    moveTray(0);
    moveStraight(10, 1000);
    moveLift(300);
    delay(500);
    moveLift(0);
    moveStraightTimed(29, 2000, 70);
    tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    trayStat = TrayStatus::idle;
    runIntk(0);

    turn(-1.8, 1000);
    moveStraight(-38, 1500);
    turn(1.8, 1000);

    runIntk(100);
    moveStraightTimed(32, 2300, 65);
    runIntk(0);

    turnTimed(-5.35, 2500, 50);
    moveStraight(44, 2000);
    runIntk(-80);
    delay(700);
    runIntk(0);

}