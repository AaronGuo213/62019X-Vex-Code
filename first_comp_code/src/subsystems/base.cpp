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

float getBaseMotorEnc() {

    return (leftBase1.get_position() + leftBase2.get_position() + rightBase1.get_position() + rightBase2.get_position()) / 4;

}

float getLeftBaseEnc() {

    return (leftBase1.get_position() + leftBase2.get_position()) / 2;

}

float getRightBaseEnc() {

    return (rightBase1.get_position() + rightBase2.get_position()) / 2;

}

void resetBaseMotorEnc() {

    leftBase1.tare_position();
    leftBase2.tare_position();
    rightBase1.tare_position();
    rightBase2.tare_position();

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

void moveStraightEnc(float distance, float theta, int time) {

    float Theta = theta + 45;
    float distVal, diffVal;
    float leftVal, rightVal;
    PID dist = initPID(0, 0, 0, 0, 0, 0);
    PID diff = initPID(0, 0, 0, 0, 0, 0);

    resetEnc();

    for(int i = 0; i < time; i ++) {

        dist.error = distance - pow(pow(getForwardEnc(), 2) + pow(getYawEnc(), 2), 0.5);
        diff.error = !(theta == 90 || theta == -90 || theta == 270) ? log(tan(theta * M_PI / 180) / (getForwardEnc() / getYawEnc())) : getYawEnc();
        distVal = runPID(&dist);
        diffVal = runPID(&diff);

        if(abs(cos(Theta * M_PI / 180)) > abs(sin(Theta * M_PI / 180))) {

            leftVal = (distVal - diffVal) * sgn(cos(Theta * M_PI / 180));
            rightVal = sin(Theta * M_PI / 180) / abs(cos(Theta * M_PI / 180)) * (distVal + diffVal);

        }

        else if(abs(cos(Theta * M_PI / 180)) < abs(sin(Theta * M_PI / 180))) {

            leftVal = cos(Theta * M_PI / 180) / abs(sin(Theta * M_PI / 180)) * (distVal - diffVal);
            rightVal = (distVal + diffVal) * sgn(sin(Theta * M_PI / 180));

        }

        runLeftBase1(leftVal);
        runLeftBase2(leftVal);
        runRightBase1(rightVal);
        runRightBase2(rightVal);

        delay(1);

    }

}

void moveStraight(float distance, float theta, int time) {

    theta += 45;
    float distVal, diffVal;
    float leftVal, rightVal;
    PID dist = initPID(0, 0, 0, 0, 0, 0);
    PID diff = initPID(0, 0, 0, 0, 0, 0);

    resetEnc();

    for(int i = 0; i < time; i ++) {

        dist.error = distance - pow(pow(getLeftBaseEnc(), 2) + pow(getRightBaseEnc(), 2), 0.5);
        diff.error = !(theta == 90 || theta == -90 || theta == 270) ? log(tan(theta * M_PI / 180) / (getRightBaseEnc() / getLeftBaseEnc())) : getRightBaseEnc();
        distVal = runPID(&dist);
        diffVal = runPID(&diff);

        if(abs(cos(theta * M_PI / 180)) > abs(sin(theta * M_PI / 180))) {

            leftVal = (distVal - diffVal) * sgn(cos(theta * M_PI / 180));
            rightVal = sin(theta * M_PI / 180) / abs(cos(theta * M_PI / 180)) * (distVal + diffVal);

        }

        else if(abs(cos(theta * M_PI / 180)) < abs(sin(theta * M_PI / 180))) {

            leftVal = cos(theta * M_PI / 180) / abs(sin(theta * M_PI / 180)) * (distVal - diffVal);
            rightVal = (distVal + diffVal) * sgn(sin(theta * M_PI / 180));

        }

        std::cout << "distance: " << pow(pow(getLeftBaseEnc(), 2) + pow(getRightBaseEnc(), 2), 0.5) << " | dist error: " << dist.error << " | diff error: " << diff.error << " | leftVal: " << leftVal << " | rightVal: " << rightVal << " | time: " << time << "\n";

        runLeftBase1(leftVal);
        runLeftBase2(leftVal);
        runRightBase1(rightVal);
        runRightBase2(rightVal);

        delay(1);

    }

}

void turn(float theta, int time) {

    float setpoint = theta * 0.2;
    float turnVal;
    PID turn = initPID(0, 0, 0, 0, 0, 0);

    resetBaseMotorEnc();

    for(int i = 0; i < time; i++) {

        turn.error = setpoint - getBaseMotorEnc();
        turnVal = runPID(&turn);

        runLeftBase1(turnVal);
        runLeftBase2(turnVal);
        runRightBase1(turnVal);
        runRightBase2(turnVal);

        delay(1);

    }

}