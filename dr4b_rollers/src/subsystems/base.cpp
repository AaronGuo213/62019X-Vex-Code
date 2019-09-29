#include "main.h"

void runLeftBase(float percent) {

    leftBase1.move_voltage(percent * 120);
    leftBase2.move_voltage(percent * 120);

}

void runRightBase(float percent) {

    rightBase1.move_voltage(percent * 120);
    rightBase2.move_voltage(percent * 120);

}

float getLeftEnc() {

    return (leftBase1.get_position() + leftBase2.get_position()) / 2;

}

float getRightEnc() {

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

    distance *= 7;
    float distVal, diffVal;
    PID dist = initPID(1, 1, 1, 1.1, 0.00006, 1);
    PID diff = initPID(1, 0, 0, 0.5, 0, 0);

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) {

        dist.error = distance - ((getLeftEnc() + getRightEnc()) / 4);
        diff.error = -getYawEnc();
        distVal = runPID(&dist);
        distVal = distVal > 90 ? 90 : distVal;
        diffVal = runPID(&diff);
        diffVal = distVal < 10 ? 0 : diffVal;

        runLeftBase(distVal - diffVal);
        runRightBase(distVal + diffVal);

        std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 4 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0);
    runRightBase(0);

}

void turn(float theta, int time) {

    float setPoint = theta * 4;
    float turnVal, dispVal;
    PID turn = initPID(1, 1, 1, 0.4, 0.00005, 1);
    PID disp = initPID(0, 0, 0, 0, 0, 0);

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) {

        turn.error = setPoint - getYawEnc();
        disp.error = (getLeftEnc() + getRightEnc()) / 4;
        turnVal = runPID(&turn);
        dispVal = runPID(&disp);

        runLeftBase(-turnVal - dispVal);
        runRightBase(turnVal - dispVal);

        std::cout << "setPoint: " << setPoint << " | currentPos: " <<getYawEnc() << " | error: " << turn.error << " | turnVal: " << turnVal << " | dispError: " << disp.error << " | dispVal: " << dispVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0);
    runRightBase(0);

}