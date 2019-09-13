#include "main.h"

void runLeftBase(float percent) {

    leftBase1.move_voltage(percent * 120); //runs the left base motor out of 12000mV

}

void runRightBase(float percent) {

    rightBase1.move_voltage(percent * 120); //runs the right base motor out of 12000mV

}

float getLeftEnc() {

    return leftBase1.get_position();

}

float getRightEnc() {

    return rightBase1.get_position();

}

void resetBaseEnc() {

    leftBase1.tare_position();
    rightBase1.tare_position();

}

float getYawEnc() {

    return yawEnc.get_value();

}

void resetYawEnc() {

    yawEnc.reset();

}

void moveStraight(float distance, int time, float maxVal) { //PID control loop to move the base to a certain relative 
                                                            //postition with minimal forwards and sideways error

    distance *= 7.00; //makes the input distance = 48 exactly one tile length, distance = 11 exactly one cube length
    float distVal, diffVal, leftVal, rightVal;
    PID dist = initPID(1, 1, 1, 1.1, 0.00006, 1); //kP = 1.1, kI = 0.00006, kD = 1
    PID diff = initPID(1, 0, 0, 0.5, 0, 0); //kP = 0.5

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        dist.error = distance - ((getLeftEnc() + getRightEnc()) / 4); //updates error for distance PID
        diff.error = -getYawEnc(); //updates error for difference PID
        distVal = runPID(&dist); //updates distVal, reference misc.cpp
        distVal = distVal > 90 ? 90 : distVal; //limits distVal to 90 in order to allow diffVal to make and impact
        diffVal = runPID(&diff); //updates diffVal, reference misc.cpp
        
        //limiting the base values one final time
        leftVal = distVal - diffVal;
        leftVal > maxVal ? maxVal : leftVal;
        rightVal = distVal + diffVal;
        rightVal > maxVal ? maxVal : rightVal;

        runLeftBase(leftVal);
        runRightBase(rightVal);

        std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 4 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0);
    runRightBase(0);

}

void turn(float theta, int time) { //PID control loop to turn a desired angle with minimal angle error

    float setPoint = theta * 4;
    float turnVal, dispVal;
    PID turn = initPID(1, 1, 1, 0.4, 0.00005, 1); //kP = 0.4, kI = 0.00005, kD = 1;
    PID disp = initPID(0, 0, 0, 0, 0, 0);

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) {

        turn.error = setPoint - getYawEnc(); //updates error for turn PID
        disp.error = (getLeftEnc() + getRightEnc()) / 4; //updates error for displacement PID
        turnVal = runPID(&turn); //updates turnVal, reference misc.cpp
        dispVal = runPID(&disp); //updates dispVal, reference misc.cpp

        runLeftBase(-turnVal - dispVal);
        runRightBase(turnVal - dispVal);

        std::cout << "setPoint: " << setPoint << " | currentPos: " <<getYawEnc() << " | error: " << turn.error << " | turnVal: " << turnVal << " | dispError: " << disp.error << " | dispVal: " << dispVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0);
    runRightBase(0);

}