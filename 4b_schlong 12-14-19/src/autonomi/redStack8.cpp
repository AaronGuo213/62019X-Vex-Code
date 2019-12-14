#include "main.h"

void redStack8() {

    //gets the first cube
    moveTray(0);
    runIntk(100);
    moveStraight(21, 900, 80);
    tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    trayStat = TrayStatus::idle;

    //gets the cubes from the 4 stack
    moveLift(atCube[5]);
    delay(1200);
    moveStraight(5.5, 700, 40);
    runIntk(100);
    liftStat = LiftStatus::manual;
    moveLift(atCube[4]);
    delay(600);
    moveLift(atCube[3]);
    delay(600);
    moveLift(atCube[2]);
    delay(600);
    moveLift(atCube[0]);
    moveStraight(5, 400, 60);
    runIntk(50);
    setLiftIdle();

    //gets the cube next to the tower
    turn(1, 500);
    runIntk(100);
    moveStraightTimed(20, 1500);
    //runIntk(0);

    //gets the stray cube near the goal
    turnTimed(5.3, 1400, 80);
    moveTray(200);
    delay(300);
    runIntk(100);
    moveStraightTimed(38, 1600, 80);
    runIntk(0);
    leftIntk.move_relative(-150, 50);
    rightIntk.move_relative(-150, 50);
    moveStraight(-2, 400);

    //outtakes
    outtake();

}