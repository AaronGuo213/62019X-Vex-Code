#include "main.h"

void moveStraight(double distance, bool stopEarly, int time, double maxVal) { 
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

}

/*void turn(double setPoint, bool stopEarly, int time, double maxVal) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal;
    double leftVal, rightVal;
    double leftDist, rightDist;
    double leftStart = getLeftEnc(), rightStart = getRightEnc();
    PID turn = initPID(1, 0, 1, 35, 0.00004, 200); //kP = 35, kD = 200;

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        leftDist = getLeftEnc() - leftStart;
        rightDist = getRightEnc() - rightStart;
        turn.error = setPoint - ((-leftDist + rightDist) / 2); //updates error for turn PID
        turnVal = runPID(&turn); //updates turnVal

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = abs(turnVal) > abs(maxVal) ? maxVal * sgn(turnVal) : turnVal;
        runBase(leftVal, rightVal); //assigns values to the motors

        //if wanted, once the robot reaches a threshhold, it will continue for efficiency
        if(stopEarly && abs(turn.error) < 0.1)
            break;

        //debugging
        std::cout << "setPoint: " << setPoint << " | leftPos: " << -leftDist << " | rightPos: " << rightDist << " | currentPos: " << (-leftDist + rightDist) / 2 << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors at the end

}*/

void turn(double angle, bool stopEarly, int time, double maxVal) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal, leftVal, rightVal;
    double lastLeft = getLeftEnc(), lastRight = getRightEnc();
    double leftDist, rightDist;
    const double trackerWheelDist = 5.44;
    double currentAngle = 0;
    PID turn = initPID(1, 0, 0, 2, 0.00004, 10); //kP = 35, kD = 200;

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        leftDist = getLeftEnc() - lastLeft;
        rightDist = getRightEnc() - lastRight;
        lastLeft = getLeftEnc();
        lastRight = getRightEnc();
        currentAngle += ((rightDist - leftDist) / trackerWheelDist) * 180 / PI;

        turn.error = angle - currentAngle; //updates error for turn PID
        turnVal = runPID(&turn); //updates turnVal

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = abs(turnVal) > abs(maxVal) ? maxVal * sgn(turnVal) : turnVal;
        runBase(leftVal, rightVal); //assigns values to the motors

        //if wanted, once the robot reaches a threshhold, it will continue for efficiency
        if(stopEarly && abs(turn.error) < 0.1)
            break;

        //debugging
        std::cout << "setPoint: " << angle << " | currentPos: " << currentAngle << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";

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

void curveBaseVel(double maxLeftRPM, double maxRightRPM, double fastSideDist) {
    //curving using the built in velocity rpm and slew rate

    resetBaseEnc();
    double maxAccel = 7;
    double leftRPM = 0, rightRPM = 0;
    //runs until a certain distance is achieved
    while(abs(getLeftEnc()) < abs(fastSideDist) && abs(getRightEnc()) < abs(fastSideDist)) {
        
        //proportionally updates the velocity of the right side if it's slower
        if(abs(maxLeftRPM) > abs(maxRightRPM)) {
            //if the goalRPM is reachable now, make the velocity the goalRPM
            if(abs(leftRPM) + abs(maxAccel) >= abs(maxLeftRPM)) {
                leftRPM = maxLeftRPM;
                rightRPM = maxRightRPM;
            }
            //otherwise increase the RPM of the motors proportionally
            else {
                leftRPM += maxAccel * sgn(maxLeftRPM);
                rightRPM = leftRPM * maxRightRPM / maxLeftRPM;
            }
            std::cout << "leftRPM: " << leftRPM << " | rightRPM: " << rightRPM << " | goalDist: " << fastSideDist <<  " | leftDist: " << getLeftEnc() << std::endl;
        }

        //proportionally updates the velocity of the left side if it's slower
        else if(abs(maxRightRPM) > abs(maxLeftRPM)) {
            //if the goalRPM is reachable now, make the velocity the goalRPM
            if(abs(rightRPM) + abs(maxAccel) >= abs(maxRightRPM)) {
                leftRPM = maxLeftRPM;
                rightRPM = maxRightRPM;
            }
            //otherwise increase the RPM of the motors proportionally
            else {
                rightRPM += maxAccel * sgn(maxRightRPM);
                leftRPM = rightRPM * maxLeftRPM / maxRightRPM;
            }
            std::cout << "leftRPM: " << leftRPM << " | rightRPM: " << rightRPM << " | goalDist: " << fastSideDist <<  " | rightDist: " << getRightEnc() << std::endl;
        }

        //if they are equal, just make both velocities max immediately
        else {
            leftRPM = maxLeftRPM;
            rightRPM = maxRightRPM;
        }

        //updates the velocity PID
        runBaseVel(leftRPM, rightRPM);
        delay(10);

    }

    //stops all base motors
    runBaseVel(0, 0);

}