#include "main.h"

/*void moveStraight(double distance, bool stopEarly, int time, double maxVal) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    double distVal, diffVal, leftVal, rightVal;
    double leftDist, rightDist;
    double leftStart = getLeftEnc(), rightStart = getRightEnc();
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 200, 0, 0); //kP = 200

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        leftDist = getLeftEnc() - leftStart;
        rightDist = getRightEnc() - rightStart;
        dist.error = distance - (leftDist + rightDist) / 2; //updates error for distance PID
        diff.error = (leftDist - rightDist) / 2; //updates error for straightness/difference PID
        distVal = runPID(&dist); //updates distVal
        diffVal = runPID(&diff); //updates diffVal
        
        //limits the influence of the diffVal when near the setpoint
        diffVal = abs(dist.error) < 100 ? diffVal * 0.1 : diffVal;
        //limits the values before sending them to the motors
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        leftVal = distVal - diffVal;
        rightVal = distVal + diffVal;

        //if wanted, once the robot reaches a threshhold, it will move on for efficiency
        if(stopEarly && abs(dist.error) < 0.2)
            break;

        runBase(leftVal, rightVal); //assigns the values to the motors

        //debugging
        std::cout << "setPoint: " << distance << " | currentPos: " << (leftDist + rightDist) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors

}*/

void moveStraight(double distance, bool stopEarly, int time, double maxVal) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    double distVal, diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double currentLeft, currentRight;
    double lastLeft = leftStart, lastRight = rightStart;
    double leftDist, rightDist, angle = 0; //variables for position and angle
    const double WHEEL_DIST = 4.54;
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 1, 0, 0); //kP = 200

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        currentLeft = getLeftEnc(); //updates current encoder values
        currentRight = getRightEnc();
        leftDist = currentLeft - leftStart; //updates current position
        rightDist = currentRight - rightStart;
        angle += (((currentRight - lastRight) - (currentLeft - lastLeft)) / WHEEL_DIST) * 180 / PI; //updates angle
        lastLeft = currentLeft; //sets up the last values for the next iteration
        lastRight = currentRight;

        dist.error = distance - (leftDist + rightDist) / 2; //updates error for distance PID
        diff.error = -angle; //updates error for straightness/difference PID
        distVal = runPID(&dist); //updates distVal
        diffVal = runPID(&diff); //updates diffVal
        
        //limits the influence of the diffVal when near the setpoint
        diffVal = abs(dist.error) < 2 ? diffVal * 0.1 : diffVal;
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

void turn(double angle, bool stopEarly, int time, double maxVal) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal, leftVal, rightVal;
    double lastLeft = getLeftEnc(), lastRight = getRightEnc();
    double leftDist, rightDist;
    const double WHEEL_DIST = 4.54;
    double currentAngle = 0;
    PID turn = initPID(1, 1, 1, 1.9, 0.00002, 9); //kP = 1.8, kI = 0.00002, kD = 9;

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

void curveBasePID(double leftSetPoint, double rightSetPoint, int time, double maxVal) { //10.75

    double diffVal, leftVal, rightVal; //power values for the motors
    double leftStart = getLeftEnc(), rightStart = getRightEnc(); //marks the staring spot
    double currentLeft, currentRight;
    double leftDist, rightDist; //variables for position and angle
    const double WHEEL_DIST = 4.54;
    PID dist = initPID(1, 1, 1, 10, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 5, 0, 0); //kP = 200

    for(int i = 0; i < time; i+=10) {

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

void curveBaseVel(double leftSetPoint, double rightSetPoint, int time, double maxVal) {

    double lastLeft = getLeftEnc(), lastRight = getRightEnc();
    double leftDiff, rightDiff;
    double leftDist = 0, rightDist = 0;
    double leftVal, rightVal, diffVal = 0, tempMaxVal;
    const double WHEEL_DIST = 4.54;
    PID dist = initPID(1, 1, 1, 10, 0.004, 10); //kP = 9, kI = 0.004, kD = 10

    for(int i = 0; i < time; i+=50) {

        leftDiff = getLeftEnc() - lastLeft;
        rightDiff = getRightEnc() - lastRight;
        lastLeft = getLeftEnc();
        lastRight = getRightEnc();
        leftDist += leftDiff;
        rightDist += rightDiff;

        if(abs(leftSetPoint) > abs(rightSetPoint)) {
            dist.error = leftSetPoint - leftDist;
            leftVal = runPID(&dist);
            rightVal = leftVal * rightSetPoint / leftSetPoint;
            if(abs(leftVal) > abs(maxVal)) {
                tempMaxVal = leftVal;
                leftVal *= abs(maxVal / tempMaxVal);
                rightVal *= abs(maxVal / tempMaxVal);
            }
            diffVal += leftDiff - (rightDiff * leftSetPoint / rightSetPoint) / 10;
            leftVal = speedToVolt(leftVal);
            rightVal = speedToVolt(rightVal);
            runBase(leftVal, rightVal + diffVal);
        }

        else {
            dist.error = rightSetPoint - rightDist;
            rightVal = runPID(&dist);
            leftVal = rightVal * leftSetPoint / rightSetPoint;
            if(abs(rightVal) > abs(maxVal)) {
                tempMaxVal = rightVal;
                rightVal *= abs(maxVal / tempMaxVal);
                leftVal *= abs(maxVal / tempMaxVal);
            }
            diffVal += rightDiff - (leftDiff * rightSetPoint / leftSetPoint) / 10;
            rightVal = speedToVolt(rightVal);
            leftVal = speedToVolt(leftVal);
            runBase(leftVal + diffVal, rightVal);
        }

        //debugging
        std::cout << "leftSetPoint: " << leftSetPoint << " | leftDist: " << leftDist << " | rightSetPoint: " << rightSetPoint << " | rightDist: " << rightDist << std::endl;
        std::cout << "dist.error: " << dist.error << " | leftVal: " << leftVal << " | rightVal: " << rightVal << " | diffVal: " << diffVal << " | time: " << i << "\n\n";

        delay(50);

    }
    runBase(0);

}