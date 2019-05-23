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

    return (leftBase1.get_position() - leftBase2.get_position() + rightBase1.get_position() - rightBase2.get_position()) / 4;

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

/*void moveStraightEnc(float distance, float theta, int time) {

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

}*/

void moveStraight(float distance, float theta, int time) {

    theta += 45;
    float distVal, diffVal, highVal, lowVal;
    float leftVal, rightVal;
    PID dist = initPID(1, 0, 1, 0.4, 0, 1);
    PID diff = initPID(1, 0, 0, 0.1, 0, 1);

    resetBaseMotorEnc();

    for(int i = 0; i < time; i ++) {

        dist.error = distance - pow(pow(getLeftBaseEnc(), 2) + pow(getRightBaseEnc(), 2), 0.5);
        distVal = runPID(&dist) > 190 ? 190 : runPID(&dist);
        //diff.error = -getRightBaseEnc() * cos(theta * M_PI / 180) + getLeftBaseEnc() * sin(theta * M_PI / 180);
        diff.error = (rightBase1.get_actual_velocity() + rightBase2.get_actual_velocity()) / 2 * cos(theta * M_PI / 180) - (leftBase1.get_actual_velocity() + leftBase2.get_actual_velocity()) / 2 * sin(theta * M_PI / 180) + -getRightBaseEnc() * cos(theta * M_PI / 180) + getLeftBaseEnc() * sin(theta * M_PI / 180);
        diffVal = runPID(&diff);

        highVal = distVal + diffVal > 200 ? 200 : distVal + diffVal;
        lowVal = distVal - diffVal > 200 ? 200 : distVal - diffVal;

        if(abs(cos(theta * M_PI / 180)) > abs(sin(theta * M_PI / 180))) {

            leftVal = lowVal * sgn(cos(theta * M_PI / 180));
            rightVal = sin(theta * M_PI / 180) / abs(cos(theta * M_PI / 180)) * highVal;

        }

        else if(abs(cos(theta * M_PI / 180)) < abs(sin(theta * M_PI / 180))) {

            leftVal = cos(theta * M_PI / 180) / abs(sin(theta * M_PI / 180)) * lowVal;
            rightVal = highVal * sgn(sin(theta * M_PI / 180));

        }

        //std::cout << getLeftBaseEnc() << " | " << getRightBaseEnc() << " | " << pow(pow(getLeftBaseEnc(), 2) + pow(getRightBaseEnc(), 2), 0.5) << "\n";
        std::cout << "distance: " << pow(pow(getLeftBaseEnc(), 2) + pow(getRightBaseEnc(), 2), 0.5) << " | dist error: " << dist.error << " | diff error: " << diff.error << " | leftVal: " << leftVal << " | rightVal: " << rightVal << " | time: " << i << "\n";
        //std::cout << leftBase1.get_actual_velocity() << " | " << leftBase2.get_actual_velocity() << " | " << rightBase1.get_actual_velocity() << " | " << rightBase2.get_actual_velocity() << "\n";

        /*if(i < 50) {
            leftVal *= i / 50;
            rightVal *= i / 50;
        }*/

        runLeftBase1(leftVal);
        runLeftBase2(leftVal);
        runRightBase1(rightVal);
        runRightBase2(rightVal);

        delay(1);

    }

    runLeftBase1(0);
    runLeftBase2(0);
    runRightBase1(0);
    runRightBase2(0);

}

void turn(float theta, int time) {

    float setPoint = -theta * 5.4;
    float turnVal;
    PID turn = initPID(1, 0, 0, 0.45, 0, 0);

    resetBaseMotorEnc();

    for(int i = 0; i < time; i++) {

        turn.error = setPoint - getBaseMotorEnc();
        turnVal = runPID(&turn);

        runLeftBase1(turnVal);
        runLeftBase2(-turnVal);
        runRightBase1(turnVal);
        runRightBase2(-turnVal);

        //std::cout << leftBase1.get_position() << " | " << leftBase2.get_position() << " | " << rightBase1.get_position() << " | " << rightBase2.get_position() << " | " << turnVal << "\n";
        std::cout << getBaseMotorEnc() << " | " << setPoint << " | " << turnVal << "\n";

        delay(1);

    }

}