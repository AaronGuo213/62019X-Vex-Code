#include "main.h"

void runLeftBase(float leftBaseVal) {

    leftBase1.move_velocity(leftBaseVal);
    leftBase2.move_velocity(leftBaseVal);

}

void runRightBase(float rightBaseVal) {

    rightBase1.move_velocity(rightBaseVal);
    rightBase2.move_velocity(rightBaseVal);

}

float leftBaseRemap(float r, float theta) {

    theta += 45;
    float leftBaseVal;

    if(abs(tan(theta)) <= 1)
        leftBaseVal = r;

    else if(abs(tan(theta)) > 1)
        leftBaseVal = r * cos(theta) / abs(sin(theta));

}

float rightBaseRemap(float r, float theta) {

    theta += 45;
    float rightBaseVal;

    if(abs(tan(theta)) >= 1)
        rightBaseVal = r;

    else if(abs(tan(theta)) < 1)
        rightBaseVal = r * sin(theta) / abs(cos(theta));

}

float getForwardEnc() {

    return (leftEnc.get_value() + rightEnc.get_value()) / 2;

}

float getYawEnc() {

    return yawEnc.get_value();

}

void resetLeftEnc() {

    leftEnc.reset();

}

void resetRightEnc() {

    rightEnc.reset();

}

void resetYawEnc() {

    yawEnc.reset();

}

void resetEnc() {

    resetLeftEnc();
    resetRightEnc();
    resetYawEnc();

}

void moveStraight(float distance, float theta, int time) {

    float Theta = theta + 45;
    float distVal, diffVal;
    float leftVal, rightVal;

    PID dist = initPID(0, 0, 0, 0, 0, 0);
    PID diff = initPID(0, 0, 0, 0, 0, 0);

    resetEnc();

    for(int i = 0; i < time; i ++) {

        dist.error = distance - pow(pow(getForwardEnc(), 2) + pow(getYawEnc(), 2), 0.5);
        diff.error = tan(theta) - (getForwardEnc() / getYawEnc());

        distVal = runPID(&dist);
        diffVal = runPID(&diff);

        if(cos(Theta) > sin(Theta)) {

            leftVal = distVal - diffVal;
            rightVal = sin(Theta) / abs(cos(theta)) * (distVal + diffVal);

        }

        else if(cos(Theta) < sin(Theta)) {

            leftVal = cos(Theta) / abs(sin(Theta)) * (distVal - diffVal);
            rightVal = distVal + diffVal;

        }

        runLeftBase(leftVal);
        runRightBase(rightVal);

    }

}