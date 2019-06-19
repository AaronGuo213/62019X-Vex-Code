#include "main.h"

void runLeftBase1(float percentage) {

    leftBase1.move_voltage(percentage * 120);

}

void runLeftBase2(float percentage) {
    
    leftBase2.move_voltage(percentage * 120);

}

void runRightBase1(float percentage) {

    rightBase1.move_voltage(percentage * 120);

}

void runRightBase2(float percentage) {

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

float getYawEnc() {

    return yawEnc.get_value();

}

void resetYawEnc() {

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

        runLeftBase1(distVal - diffVal);
        runLeftBase2(distVal - diffVal);
        runRightBase1(distVal + diffVal);
        runRightBase2(distVal + diffVal);

        delay(1);

    }

    runLeftBase1(0);
    runLeftBase2(0);
    runRightBase1(0);
    runRightBase2(0);

}

void turn(float theta, int time) {

    float setPoint = theta * 1;
    float turnVal, dispVal;
    PID turn = initPID(0, 0, 0, 0, 0, 0);
    PID disp = initPID(0, 0, 0, 0, 0, 0);

    resetBaseEnc();

    for(int i = 0; i < time; i++) {

        turn.error = setPoint - getBaseEnc();
        disp.error = getLeftBaseEnc() - getRightBaseEnc();
        turnVal = runPID(&turn);
        dispVal = runPID(&disp);

        runLeftBase1(turnVal - dispVal);
        runLeftBase2(turnVal - dispVal);
        runRightBase1(turnVal - dispVal);
        runRightBase2(-turnVal - dispVal);

        delay(1);

    }

    runLeftBase1(0);
    runLeftBase2(0);
    runRightBase1(0);
    runRightBase2(0);

}