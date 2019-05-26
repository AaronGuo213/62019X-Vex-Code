#include "main.h"

void runLeftBase(float percentage) {

    leftBase1.move_voltage(percentage * 120);
    leftBase2.move_voltage(percentage * 120);

}

void runRightBase(float percentage) {

    rightBase1.move_voltage(percentage * 120);
    rightBase2.move_voltage(percentage * 120);

}

float getBaseEnc() {

    return (leftBase1.get_position() + leftBase2.get_position() + rightBase1.get_position() + rightBase2.get_position()) / 4;

}

float getLeftBaseEnc() {

    return (leftBase1.get_position() + leftBase2.get_position()) / 2;

}

float getRightBaseEnc() {

    return (rightBase1.get_position() + rightBase2.get_position()) / 2;

}

void resetBaseEnc() {

    leftBase1.tare_position();
    leftBase2.tare_position();
    rightBase1.tare_position();
    rightBase2.tare_position();

}

float getForeEnc() {

    return foreEnc.get_value();

}

float getYawEnc() {

    return yawEnc.get_value();

}

void resetEnc() {

    foreEnc.reset();
    yawEnc.reset();

}

void moveStraight(float distance, int time) {

    float distVal, diffVal;
    PID dist = initPID(0, 0, 0, 0, 0, 0);
    PID diff = initPID(0, 0, 0, 0, 0, 0);

    resetBaseEnc();

    for(int i = 0; i < time; i ++) {

        dist.error = distance - getBaseEnc();
        diff.error = getLeftBaseEnc() - getRightBaseEnc();
        distVal = runPID(&dist);
        diffVal = runPID(&diff);

        runLeftBase(distVal - diffVal);
        runRightBase(distVal + diffVal);

        delay(1);

    }

    runLeftBase(0);
    runRightBase(0);

}

void turn(float theta, int time) {

    float setPoint = theta * 0;
    float turnVal, dispVal;
    PID turn = initPID(0, 0, 0, 0, 0, 0);
    PID disp = initPID(0, 0, 0, 0, 0, 0);

    resetBaseEnc();

    for(int i = 0; i < time; i++) {

        turn.error = setPoint - getBaseEnc();
        disp.error = getLeftBaseEnc() - getRightBaseEnc();
        turnVal = runPID(&turn);
        dispVal = runPID(&disp);

        runLeftBase(turnVal - dispVal);
        runRightBase(-turnVal - dispVal);

        delay(1);

    }

    runLeftBase(0);
    runRightBase(0);

}