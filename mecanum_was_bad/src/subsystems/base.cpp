#include "main.h"

void runLeftBase(float percentage) {

    leftBase1.move_voltage(percentage * 120);
    leftBase2.move_voltage(percentage * 120);

}

void runRightBase(float percentage) {

    rightBase1.move_voltage(percentage * 120);
    rightBase2.move_voltage(percentage * 120);

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

    distance *= 7.2;
    time /= 5;
    float distVal, diffVal;
    PID dist = initPID(1, 0, 1, 0.8, 0, 1);
    PID diff = initPID(0, 0, 0, 0, 0, 0);

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i++) {

        dist.error = distance - ((getLeftEnc() + getRightEnc()) / 4);
        diff.error = (getLeftEnc() - getRightEnc()) / 4;
        distVal = runPID(&dist);
        diffVal = runPID(&diff);

        runLeftBase(distVal - diffVal);
        runRightBase(distVal + diffVal);

        if(!(i % 10));
            std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 4 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(5);

    }

    runLeftBase(0);
    runRightBase(0);

}

void turn(float theta, int time) {

    float setPoint = theta * 1;
    float turnVal, dispVal;
    PID turn = initPID(0, 0, 0, 0, 0, 0);
    PID disp = initPID(0, 0, 0, 0, 0, 0);

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i++) {

        turn.error = setPoint - (-getLeftEnc() + getRightEnc()) / 2;
        disp.error = getLeftEnc() + getRightEnc();
        turnVal = runPID(&turn);
        dispVal = runPID(&disp);

        runLeftBase(turnVal - dispVal);
        runRightBase(-turnVal - dispVal);

        std::cout << "setPoint: " << setPoint << " | currentPos: " << (-getLeftEnc() + getRightEnc()) / 2 << " | error: " << turn.error << " | turnVal: " << turnVal << " | dispError: " << disp.error << " | dispVal: " << dispVal << " | time: " << i << "\n";

        delay(1);

    }

    runLeftBase(0);
    runRightBase(0);

}