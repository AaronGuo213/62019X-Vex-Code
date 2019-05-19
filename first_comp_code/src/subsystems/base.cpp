#include "main.h"

void runLeftBase1(float percentage) {

    leftBase1.move_velocity(percentage * 2);

}

void runLeftBase2(float percentage) {

    leftBase2.move_velocity(percentage * 2);

}

void runRightBase1(float percentage) {

    rightBase1.move_velocity(percentage * 2);

}

void runRightBase2(float percentage) {

    rightBase2.move_velocity(percentage * 2);

}

float leftBaseRemap(float r, float theta) {

    theta += 45;
    float leftBaseVal;

    if(theta == 0 || theta == 180)
        leftBaseVal = r;

    else if(abs(cos(theta * M_PI / 180)) >= abs(sin(theta * M_PI / 180)))
        leftBaseVal = r * sgn(cos(theta * M_PI / 180));

    else if(abs(cos(theta * M_PI / 180)) < abs(sin(theta * M_PI / 180)))
        leftBaseVal = r * cos(theta * M_PI / 180) / abs(sin(theta * M_PI / 180));

    return leftBaseVal;

}

float rightBaseRemap(float r, float theta) {

    theta += 45;
    float rightBaseVal;

    if(theta == 0 || theta == 180)
        rightBaseVal = r;

    else if(abs(sin(theta * M_PI / 180)) >= abs(cos(theta * M_PI / 180)))
        rightBaseVal = r * sgn(sin(theta * M_PI / 180));

    else if(abs(sin(theta * M_PI / 180)) < abs(cos(theta * M_PI / 180)))
        rightBaseVal = r * sin(theta * M_PI / 180) / abs(cos(theta * M_PI / 180));

    return rightBaseVal;

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