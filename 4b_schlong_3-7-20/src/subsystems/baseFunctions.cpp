#include "main.h"

/*======================
DRIVE STRAIGHT FUNCTIONS
======================*/

void moveStraight(double distance, double maxVal) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    double distVal, diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double leftDist, rightDist; //variables for position
    double startAngle = getAngle();
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 10, 0, 0); //kP = 10

    for(int i = 0 ; true; i+=10) {

        //updates current distance, PID errors, and motor values
        leftDist = getLeftEnc() - leftStart;
        rightDist = getRightEnc() - rightStart;

        dist.error = distance - (leftDist + rightDist) / 2;
        diff.error = startAngle - getAngle();
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
        if((abs(dist.error) < 0.5 && isBaseSettled()) || (i > 200 && isBaseStopped()))
            break;

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << (leftDist + rightDist) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors

}

void moveStraight(double distance, bool stopEarly, int time, double maxVal) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    double distVal, diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double leftDist, rightDist; //variables for position
    double startAngle = getAngle();
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 10, 0, 0); //kP = 200

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        leftDist = getLeftEnc() - leftStart; //updates current position
        rightDist = getRightEnc() - rightStart;

        dist.error = distance - (leftDist + rightDist) / 2; //updates error for distance PID
        diff.error = startAngle - getAngle();
        distVal = runPID(&dist); //updates distVal
        diffVal = runPID(&diff); //updates diffVal
        
        //limits the influence of the diffVal when near the setpoint
        diffVal = abs(dist.error) < 4 ? diffVal * 0.1 : diffVal;
        //limits the values before sending them to the motors
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        leftVal = distVal - diffVal;
        rightVal = distVal + diffVal;

        //if wanted, once the robot reaches a threshhold, it will move on for efficiency
        if(stopEarly && abs(dist.error) < 0.5)
            break;

        runBase(leftVal, rightVal); //assigns the values to the motors

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << (leftDist + rightDist) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors

}

void moveStraight(double distance, double switchDist, bool stopEarly, int time, double maxVal1, double maxVal2) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    double maxVal = maxVal1;
    double distVal, diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double startAngle = getAngle();
    double leftDist, rightDist; //variables for position
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 3, 0, 0); //kP = 200

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        leftDist = getLeftEnc() - leftStart; //updates current position
        rightDist = getRightEnc() - rightStart;

        dist.error = distance - (leftDist + rightDist) / 2; //updates error for distance PID
        diff.error = startAngle - getAngle();
        distVal = runPID(&dist); //updates distVal
        diffVal = runPID(&diff); //updates diffVal
        
        //limits the influence of the diffVal when near the setpoint
        diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal;
        //limits the values before sending them to the motors
        if(abs((leftDist + rightDist) / 2) >= abs(switchDist))
            maxVal = maxVal2;
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        leftVal = distVal - diffVal;
        rightVal = distVal + diffVal;

        //if wanted, once the robot reaches a threshhold, it will move on for efficiency
        if(stopEarly && abs(dist.error) < 0.5)
            break;

        runBase(leftVal, rightVal); //assigns the values to the motors

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << (leftDist + rightDist) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors

}

void moveStraightCut(double distance, double setPoint, double maxVal) {
    //PID control loop to move the base to a certain relative 
    //postition as fast and accurately as possible, leading into another drive function

    double distVal, diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double leftDist, rightDist; //variables for position
    double startAngle = getAngle();
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 3, 0, 0); //kP = 200

    while(true) { //updates every 10 ms

        leftDist = getLeftEnc() - leftStart; //updates current position
        rightDist = getRightEnc() - rightStart;

        dist.error = distance - (leftDist + rightDist) / 2; //updates error for distance PID
        diff.error = startAngle - getAngle();
        distVal = runPID(&dist); //updates distVal
        diffVal = runPID(&diff); //updates diffVal
        
        //limits the influence of the diffVal when near the setpoint
        diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal;
        //limits the values before sending them to the motors
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        leftVal = distVal - diffVal;
        rightVal = distVal + diffVal;

        //if wanted, once the robot reaches a threshhold, it will move on for efficiency
        if(abs(dist.error) >= abs(distance))
            break;

        runBase(leftVal, rightVal); //assigns the values to the motors

        //debugging
        std::cout << "setPoint: " << distance << " | pos: " << (leftDist + rightDist) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << "\n";

        delay(10); //every 10 ms

    }

}

/*============
TURN FUNCTIONS
============*/

void turn(double angle, double maxVal) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal, leftVal, rightVal;
    double lastLeft = getLeftEnc(), lastRight = getRightEnc();
    double leftDist, rightDist;
    const double WHEEL_DIST = 4.54;
    double currentAngle = 0;
    PID turn = initPID(1, 1, 1, 2.5, 0.00001, 10); //kP = 2.5, kI = 0.00001, kD = 10;

    for(int i = 0; true; i+=10) {

        //updates angle, PID error, and motor values
        leftDist = getLeftEnc() - lastLeft;
        rightDist = getRightEnc() - lastRight;
        lastLeft = getLeftEnc();
        lastRight = getRightEnc();
        currentAngle += ((rightDist - leftDist) / WHEEL_DIST) * 180 / PI;

        turn.error = angle - currentAngle;
        turnVal = runPID(&turn);

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = -leftVal;
        runBase(leftVal, rightVal);

        //stops when threshhold is reached and speed is slow enough or robot stops
        if((abs(turn.error) < 1 && isBaseSettled()) || (i > 200 && isBaseStopped()))
            break;

        //debugging
        std::cout << "setPoint: " << angle << " | currentPos: " << currentAngle << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";
        //std::cout << "leftDist: " << leftDist << " | rightDist: " << rightDist << std::endl;

        delay(10); //every 10 ms

    }

    runBase(0, 0); //stops the motors at the end

}

void turn(double angle, bool stopEarly, int time, double maxVal) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal, leftVal, rightVal;
    double lastLeft = getLeftEnc(), lastRight = getRightEnc();
    double leftDist, rightDist;
    const double WHEEL_DIST = 4.54;
    double currentAngle = 0;
    PID turn = initPID(1, 1, 1, 2.5, 0.00001, 10); //kP = 2.5, kI = 0.00001, kD = 10;

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        leftDist = getLeftEnc() - lastLeft; //calculates the angle traveled so far
        rightDist = getRightEnc() - lastRight;
        lastLeft = getLeftEnc();
        lastRight = getRightEnc();
        currentAngle += ((rightDist - leftDist) / WHEEL_DIST) * 180 / PI;

        turn.error = angle - currentAngle; //updates error for turn PID
        turnVal = runPID(&turn); //updates turnVal

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = -leftVal;
        runBase(leftVal, rightVal); //assigns values to the motors

        //if wanted, once the robot reaches a threshhold, it will continue for efficiency
        if(stopEarly && abs(turn.error) < 1)
            break;

        //debugging
        std::cout << "setPoint: " << angle << " | currentPos: " << currentAngle << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";
        //std::cout << "leftDist: " << leftDist << " | rightDist: " << rightDist << std::endl;

        delay(10);

    }

    runBase(0, 0); //stops the motors at the end

}

void turnRelative(double angle, double maxVal) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal, leftVal, rightVal;
    double startAngle = getAngle(), currentAngle;
    PID turn = initPID(1, 1, 1, 2.5, 0.00001, 10); //kP = 2.5, kI = 0.00001, kD = 10;

    for(int i = 0; true; i+=10) {

        //updates PID error and motor values
        currentAngle = getAngle() - startAngle;
        turn.error = angle - currentAngle;
        turnVal = runPID(&turn);

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = -leftVal;
        runBase(leftVal, rightVal);

        //stops when threshhold is reached and speed is slow enough or robot stops
        if((abs(turn.error) < 1 && isBaseSettled()) || (i > 200 && isBaseStopped()))
            break;

        //debugging
        std::cout << "setPoint: " << angle << " | currentPos: " << currentAngle << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";
        //std::cout << "leftDist: " << leftDist << " | rightDist: " << rightDist << std::endl;

        delay(10); //every 10 ms

    }

    runBase(0, 0); //stops the motors at the end

}

void turnAbsolute(double angle, double maxVal) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal, leftVal, rightVal;
    PID turn = initPID(1, 1, 1, 2.5, 0.00001, 10); //kP = 2.5, kI = 0.00001, kD = 10;

    for(int i = 0; true; i+=10) {

        //updates PID error and motor values
        turn.error = angle - getAngle();
        turnVal = runPID(&turn);

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = -leftVal;
        runBase(leftVal, rightVal);

        //stops when threshhold is reached and speed is slow enough or robot stops
        if((abs(turn.error) < 1 && isBaseSettled()) || (i > 200 && isBaseStopped()))
            break;

        //debugging
        std::cout << "setPoint: " << angle << " | currentPos: " << getAngle() << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";
        //std::cout << "leftDist: " << leftDist << " | rightDist: " << rightDist << std::endl;

        delay(10); //every 10 ms

    }

    runBase(0, 0); //stops the motors at the end

}

void turnToCorner(double initVal) {

    runBase(-initVal, initVal); //turns and finds the corner(least sonar value)
    double lastDist = sonar.get_value();
    while(lastDist > sonar.get_value()) {
        lastDist = sonar.get_value();
        delay(50);
    }

    double error = 1, turnVal, leftVal, rightVal; //uses P loop to turn to the corner
    while(abs(error) > 0.3 && !isBaseStopped()) { //if the robot reaches a threshold or stops moving
        error = sonar.get_value() - lastDist;
        turnVal = error * 20;
        leftVal = turnVal * sgn(initVal);
        rightVal = -leftVal;
        runBase(leftVal, rightVal);
    }
    runBase(0);

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

void curveBasePID(double leftSetPoint, double rightSetPoint, double maxVal) { //10.75

    double diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double currentLeft, currentRight;
    double leftDist, rightDist; //current position
    const double WHEEL_DIST = 4.54;
    PID dist = initPID(1, 1, 1, 10, 0.004, 10); //kP = 10, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 5, 0, 0); //kP = 5

    for(int i = 0; true; i+=10) {

        //updates current position
        currentLeft = getLeftEnc();
        currentRight = getRightEnc();
        leftDist = currentLeft - leftStart;
        rightDist = currentRight - rightStart;

        if(abs(leftSetPoint) > abs(rightSetPoint)) {
            dist.error = leftSetPoint - leftDist;
            diff.error = (rightDist * leftSetPoint / rightSetPoint) - leftDist;
            leftVal = runPID(&dist); //uses dist PID to determine speed for left side of the base
            leftVal = abs(leftVal) > maxVal ? maxVal * sgn(leftVal) : leftVal;
            rightVal = leftVal * rightSetPoint / leftSetPoint * WHEEL_DIST / 10.75; //then uses ratios to get the speed for right side of the base
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
            leftVal = rightVal * leftSetPoint / rightSetPoint * WHEEL_DIST / 10.75; //then uses ratios to get the speed for left side of the base
            leftVal = speedToVolt(leftVal * 2); //conversion to voltage
            rightVal = speedToVolt(rightVal * 2);
            diffVal = runPID(&diff);
            diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal; //limits power of diffVal when close to target
            rightVal += diffVal;
            leftVal -= diffVal;
        }

        //stops when threshhold is reached and speed is slow enough or robot stops
        if((abs(dist.error) < 0.5 && isBaseSettled()) || (i > 200 && isBaseStopped()))
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

void curveBasePID(double leftSetPoint, double rightSetPoint, int time, double maxVal) { //10.75

    double diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double currentLeft, currentRight;
    double leftDist, rightDist; //current position
    const double WHEEL_DIST = 4.54;
    PID dist = initPID(1, 1, 1, 10, 0.004, 10); //kP = 10, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 5, 0, 0); //kP = 5

    for(int i = 0; i < time; i+=10) {

        //updates current position
        currentLeft = getLeftEnc();
        currentRight = getRightEnc();
        leftDist = currentLeft - leftStart;
        rightDist = currentRight - rightStart;

        if(abs(leftSetPoint) > abs(rightSetPoint)) {
            dist.error = leftSetPoint - leftDist;
            diff.error = (rightDist * leftSetPoint / rightSetPoint) - leftDist;
            leftVal = runPID(&dist); //uses dist PID to determine speed for left side of the base
            leftVal = abs(leftVal) > maxVal ? maxVal * sgn(leftVal) : leftVal;
            rightVal = leftVal * rightSetPoint / leftSetPoint * WHEEL_DIST / 10.75; //then uses ratios to get the speed for right side of the base
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
            leftVal = rightVal * leftSetPoint / rightSetPoint * WHEEL_DIST / 10.75; //then uses ratios to get the speed for left side of the base
            leftVal = speedToVolt(leftVal * 2); //conversion to voltage
            rightVal = speedToVolt(rightVal * 2);
            diffVal = runPID(&diff);
            diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal; //limits power of diffVal when close to target
            rightVal += diffVal;
            leftVal -= diffVal;
        }

        //debugging
        std::cout << "leftSetPoint: " << leftSetPoint << " | leftPos: " << leftDist << " | leftVal: " << leftVal << std::endl;
        std::cout << "rightSetPoint: " << rightSetPoint << " | rightPos: " << rightDist << " | rightVal: " << rightVal << std::endl;
        std::cout << "diff error: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n\n";

        runBase(leftVal, rightVal);
        delay(10);

    }

    runBase(0);

}

void curveBasePIDCut(double leftSetPoint, double rightSetPoint, double fastSideDist, double maxVal) {

    double diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double currentLeft, currentRight;
    double leftDist, rightDist; //variables for position and angle
    const double WHEEL_DIST = 4.54;
    PID dist = initPID(1, 1, 1, 10, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 5, 0, 0); //kP = 200

    while(true) {

        currentLeft = getLeftEnc(); //updates current encoder values
        currentRight = getRightEnc();
        leftDist = currentLeft - leftStart; //updates current position
        rightDist = currentRight - rightStart;

        if(abs(leftSetPoint) > abs(rightSetPoint)) {
            dist.error = leftSetPoint - leftDist;
            diff.error = (rightDist * leftSetPoint / rightSetPoint) - leftDist;
            leftVal = runPID(&dist);
            leftVal = abs(leftVal) > maxVal ? maxVal * sgn(leftVal) : leftVal;
            rightVal = leftVal * rightSetPoint / leftSetPoint * WHEEL_DIST / 10.75;
            leftVal = speedToVolt(leftVal * 2);
            rightVal = speedToVolt(rightVal * 2);
            diffVal = runPID(&diff);
            diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal;
            leftVal += diffVal;
            rightVal -= diffVal;
            if(abs(leftDist) >= abs(fastSideDist))
                break;
        }

        else {
            dist.error = rightSetPoint - rightDist;
            diff.error = (leftDist * rightSetPoint / leftSetPoint) - rightDist;
            rightVal = runPID(&dist);
            rightVal = abs(rightVal) > maxVal ? maxVal * sgn(rightVal) : rightVal;
            leftVal = rightVal * leftSetPoint / rightSetPoint * WHEEL_DIST / 10.75;
            leftVal = speedToVolt(leftVal * 2);
            rightVal = speedToVolt(rightVal * 2);
            diffVal = runPID(&diff);
            diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal;
            rightVal += diffVal;
            leftVal -= diffVal;
            if(abs(rightDist) >= abs(fastSideDist))
                break;
        }

        //debugging
        std::cout << "leftSetPoint: " << leftSetPoint << " | leftPos: " << leftDist << " | leftVal: " << leftVal << std::endl;
        std::cout << "rightSetPoint: " << rightSetPoint << " | rightPos: " << rightDist << " | rightVal: " << rightVal << std::endl;
        std::cout << "diff error: " << diff.error << " | diffVal: " << diffVal << "\n\n";

        runBase(leftVal, rightVal);
        delay(10);

    }

    runBase(0);

}

void curveBaseCombo(double distance, double angle, int time, double maxVal) {

    double currentAngle = 0;
    double distVal, turnVal, leftVal, rightVal;
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double currentLeft, currentRight, lastLeft = leftStart, lastRight = rightStart;
    double leftDist, rightDist; //variables for position and angle
    const double WHEEL_DIST = 4.54;
    PID dist = initPID(1, 1, 1, 10, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID turn = initPID(1, 1, 1, 1.9, 0.00002, 9); //kP = 200

    for(int i = 0; i < time; i+=10) {

        currentLeft = getLeftEnc(); //updates current encoder values
        currentRight = getRightEnc();
        leftDist = currentLeft - leftStart; //updates current position
        rightDist = currentRight - rightStart;
        currentAngle += (((currentRight - lastRight) - (currentLeft - lastLeft)) / WHEEL_DIST) * 180 / PI;
        lastLeft = currentLeft;
        lastRight = currentRight;

        dist.error = distance - ((leftDist + rightDist) / 2);
        turn.error = angle - currentAngle;
        distVal = runPID(&dist);
        turnVal = runPID(&turn);

        leftVal = distVal - turnVal;
        rightVal = distVal + turnVal;
        if(abs(leftVal) > abs(maxVal) || abs(rightVal) > abs(maxVal)) {
            double temp = leftVal > rightVal ? leftVal : rightVal;
            leftVal = leftVal / temp * maxVal;
            rightVal = rightVal / temp * maxVal;
        }

        //debugging
        std::cout << "distSP: " << distance << " | currentPos: " << (leftDist + rightDist) / 2 << " | distError: " << dist.error << " | distVal: " << distVal << std::endl;
        std::cout << "turnSP: " << angle << " | currentAngle: " << currentAngle << " | turnError: " << turn.error << " | turnVal: " << turnVal << std::endl;
        std::cout << "leftVal: " << leftVal << " | rightVal: " << rightVal << " | time: " << i << "\n\n";

        runBase(leftVal, rightVal);
        delay(10);

    }

    runBase(0);

}