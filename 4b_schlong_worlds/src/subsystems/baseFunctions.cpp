#include "main.h"

/*======================
DRIVE STRAIGHT FUNCTIONS
======================*/

void moveDist(double distance, double maxVal, int time) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    resetBaseMotorEnc();
    double distVal, diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double leftDist, rightDist, currentDist; //variables for position
    double startAngle = getAngle();
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 5, 0, 0); //kP = 5
    int timeLimit = !time ? 60000 : time;

    for(int i = 0; i < timeLimit; i+=10) {

        //updates current distance, PID errors, and motor values
        leftDist = getLeftEnc() - leftStart;
        rightDist = getRightEnc() - rightStart;
        currentDist = (leftDist + rightDist) / 2;

        dist.error = distance - currentDist;
        //dist.error = distance - rightDist;
        diff.error = (getLeftEncMotors() - getRightEncMotors()) / 2;
        distVal = runPID(&dist);
        diffVal = runPID(&diff);
        
        //limits the influence of the diffVal when near the setpoint
        diffVal = abs(dist.error) < 4 ? diffVal * 0.1 : diffVal;
        //limits the values before sending them to the motors
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        leftVal = distVal - diffVal;
        rightVal = distVal + diffVal;
        runBase(leftVal, rightVal);

        //stops when threshhold is reached and speed is slow enough or robot stops
        if(!time && (i > 200 && isBaseSettled(5)))
            break;

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << currentDist << " | error: " << dist.error << " | distVal: " << distVal << " | diff error: " << diff.error <<  " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors

}

void moveDist(double distance, double switchDist, double maxVal1, double maxVal2, int time) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    resetBaseMotorEnc();
    double distVal, diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double leftDist, rightDist, currentDist; //variables for position
    double startAngle = getAngle();
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 5, 0, 0); //kP = 5
    int timeLimit = !time ? 60000 : time;
    double maxVal = maxVal1;

    for(int i = 0; i < timeLimit; i+=10) {

        //updates current distance, PID errors, and motor values
        leftDist = getLeftEnc() - leftStart;
        rightDist = getRightEnc() - rightStart;
        currentDist = (leftDist - rightDist) / 2;

        dist.error = distance - currentDist;
        //dist.error = distance - rightDist;
        diff.error = (getLeftEncMotors() - getRightEncMotors()) / 2;
        distVal = runPID(&dist);
        diffVal = runPID(&diff);
        
        //limits the influence of the diffVal when near the setpoint
        diffVal = abs(dist.error) < 4 ? diffVal * 0.1 : diffVal;
        //limits the values before sending them to the motors
        maxVal = currentDist > switchDist ? maxVal2 : maxVal1;
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        leftVal = distVal - diffVal;
        rightVal = distVal + diffVal;
        runBase(leftVal, rightVal);

        //stops when threshhold is reached and speed is slow enough or robot stops
        if(!time && (i > 200 && isBaseSettled(5)))
            break;

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << currentDist << " | error: " << dist.error << " | distVal: " << distVal << " | diff error: " << diff.error <<  " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors

}

void moveStraight(double distance, double percent) {
    //PID control loop to move the base to a certain relative 
    //postition as fast and accurately as possible, leading into another drive function

    double diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double leftDist, rightDist, currentDist; //variables for position
    double startAngle = getAngle();
    PID diff = initPID(1, 0, 0, 10, 0, 0); //kP = 10

    while(true) { //updates every 10 ms

        leftDist = getLeftEnc() - leftStart; //updates current position
        rightDist = getRightEnc() - rightStart;
        currentDist = (leftDist + rightDist) / 2;

        diff.error = getLeftEncMotors() - getRightEncMotors(); //updates straightness PID
        //diff.error = startAngle - getAngle(); //updates straightness PID
        diffVal = runPID(&diff);
        leftVal = percent - diffVal;
        rightVal = percent + diffVal;

        //robot transitions when distance is reached
        if(currentDist >= distance)
            break;

        runBase(leftVal, rightVal); //assigns the values to the motors

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << currentDist << " | diffError: " << diff.error << " | diffVal: " << diffVal << "\n";

        delay(10); //every 10 ms

    }

}

/*============
TURN FUNCTIONS
============*/

void turnRelative(double angle, double maxVal, int time) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal, leftVal, rightVal;
    double startAngle = getAngle(), currentAngle;
    PID turn;
    if(abs(angle) >= 25) //good for angles 25 degrees to 135 degrees
        turn = initPID(1, 1, 1, 2.5, 0.00001, 10); //kP = 2.5, kI = 0.00001, kD = 10;
    else //good for angles 10 degrees to 25 degrees
        turn = initPID(1, 0, 1, 5, 0, 15);
    int timeLimit = !time ? 60000 : time;

    //accounts for gyro overlap
    int overlap = 0;
    double fakeStartAngle;
    if(startAngle + angle > 180) {
        overlap = 1;
        fakeStartAngle = -360 + startAngle;
    }
    else if(startAngle + angle < -180) {
        overlap = 2;
        fakeStartAngle = 360 + startAngle;
    }

    for(int i = 0; i < timeLimit; i+=10) {

        //updates PID error and motor values
        currentAngle = getAngle() - startAngle;
        turn.error = angle - currentAngle;
        turnVal = runPID(&turn);

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = -leftVal;
        runBase(leftVal, rightVal);

        //accounts for gyro overlap
        if(overlap == 1 && currentAngle < -170)
            startAngle = fakeStartAngle;
        else if(overlap == 2 && currentAngle > 170)
            startAngle = fakeStartAngle;

        //stops when threshhold is reached and speed is slow enough or robot stops
        if(!time && (i > 200 && isBaseSettled(5)))
            break;

        //debugging
        std::cout << "setPoint: " << angle << " | currentPos: " << currentAngle << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";

        delay(10); //every 10 ms

    }

    runBase(0, 0); //stops the motors at the end

}

void turnAbsolute(double angle, double maxVal, int time) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal, leftVal, rightVal;
    PID turn;
    if(abs(angle - getAngle()) >= 25) //good for angles 25 degrees to 135 degrees
        turn = initPID(1, 1, 1, 2.5, 0.00001, 10); //kP = 2.5, kI = 0.00001, kD = 10;
    else //good for angles 10 degrees to 25 degrees
        turn = initPID(1, 0, 1, 5, 0, 15);
    int timeLimit = !time ? 60000 : time;

    for(int i = 0; i < time; i+=10) {

        //updates PID error and motor values
        turn.error = angle - getAngle();
        turnVal = runPID(&turn);

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = -leftVal;
        runBase(leftVal, rightVal);

        //stops when threshhold is reached and speed is slow enough or robot stops
        if(!time && (i > 200 && isBaseSettled(5)))
            break;

        //debugging
        std::cout << "setPoint: " << angle << " | currentPos: " << getAngle() << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";

        delay(10); //every 10 ms

    }

    runBase(0, 0); //stops the motors at the end

}

/*=============
CURVE FUNCTIONS
=============*/

void curveBase(double leftPow, double rightPow, double fastSideDist) {
    //simple curving with constant voltage until a certain distance is achieved

    double leftStart = getLeftEnc(), rightStart = getRightEnc();
    double leftDist = 0, rightDist = 0;
    runBase(leftPow, rightPow);
    while(abs(leftDist) < abs(fastSideDist) && abs(rightDist) < abs(fastSideDist)) {
        leftDist = getLeftEnc() - leftStart;
        rightDist = getRightEnc() - rightStart;
        delay(10);
    }
    runBase(0, 0);

}

void curveBasePID(double leftSetPoint, double rightSetPoint, double maxVal, int time) { //10.75

    resetBaseMotorEnc();
    double diffVal, leftVal, rightVal; //power values for the motors
    double leftDist, rightDist; //current position
    PID dist = initPID(1, 1, 1, 10, 0.004, 10); //kP = 10, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 5, 0, 0); //kP = 5
    int timeLimit = !time ? 60000 : time;

    for(int i = 0; i < time; i+=10) {

        //updates current position
        leftDist = getLeftEncMotors();
        rightDist = getRightEncMotors();

        if(abs(leftSetPoint) > abs(rightSetPoint)) {
            dist.error = leftSetPoint - leftDist;
            diff.error = (rightDist * leftSetPoint / rightSetPoint) - leftDist;
            leftVal = runPID(&dist); //uses dist PID to determine speed for left side of the base
            leftVal = abs(leftVal) > maxVal ? maxVal * sgn(leftVal) : leftVal;
            rightVal = leftVal * rightSetPoint / leftSetPoint; //then uses ratios to get the speed for right side of the base
            leftVal = speedToVolt(leftVal * 2); //conversion to voltage
            rightVal = speedToVolt(rightVal * 2);
            diffVal = runPID(&diff);
            diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal; //limits power of diffVal when close to target
            leftVal += diffVal;
            rightVal -= diffVal;
        }

        else {
            dist.error = rightSetPoint - rightDist;
            diff.error = (leftDist * rightSetPoint / leftSetPoint) - rightDist;
            rightVal = runPID(&dist); //uses dist PID to determine speed for right side of the base
            rightVal = abs(rightVal) > maxVal ? maxVal * sgn(rightVal) : rightVal;
            leftVal = rightVal * leftSetPoint / rightSetPoint; //then uses ratios to get the speed for left side of the base
            leftVal = speedToVolt(leftVal * 2); //conversion to voltage
            rightVal = speedToVolt(rightVal * 2);
            diffVal = runPID(&diff);
            diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal; //limits power of diffVal when close to target
            rightVal += diffVal;
            leftVal -= diffVal;
        }

        //the robot transitions when it stops
        if(!time && (i > 200 && isBaseSettled(5)))
            break;

        //debugging
        std::cout << "leftSetPoint: " << leftSetPoint << " | leftPos: " << leftDist << " | leftVal: " << leftVal << std::endl;
        std::cout << "rightSetPoint: " << rightSetPoint << " | rightPos: " << rightDist << " | rightVal: " << rightVal << std::endl;
        std::cout << "diff error: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n\n";

        runBase(leftVal, rightVal);
        delay(10);

    }

    runBase(0);

}

/*===
OTHER
===*/

double getDeployOffset(int time) {
    //uses encoders to get the distance the robot moves back on deploy

    double start = (getLeftEnc() + getRightEnc()) / 2;
    for(int i = 0; i < time; i+=10)
        delay(10);
    double end = (getLeftEnc() + getRightEnc()) / 2;
    return end - start;

}