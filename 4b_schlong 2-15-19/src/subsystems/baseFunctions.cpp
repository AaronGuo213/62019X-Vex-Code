#include "main.h"

void moveStraight(double distance, bool stopEarly, int time, double maxVal) { 
    //PID control loop to move the base to a certain relative 
    //postition with minimal forwards and sideways error

    double distVal, diffVal, leftVal, rightVal;
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 200, 0, 0); //kP = 200

    resetBaseEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        dist.error = distance - ((getLeftEnc() + getRightEnc()) / 2); //updates error for distance PID
        diff.error = (getLeftEnc() - getRightEnc()) / 2; //updates error for straightness/difference PID
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
        std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors

}

void turn(double setPoint, bool stopEarly, int time, double maxVal) { 
    //PID control loop to turn a desired angle with minimal angle error

    double turnVal;
    double leftVal, rightVal;
    PID turn = initPID(1, 0, 1, 35, 0.00004, 200); //kP = 35, kD = 200;

    resetBaseEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        turn.error = setPoint - ((-getLeftEnc() + getRightEnc()) / 2); //updates error for turn PID
        turnVal = runPID(&turn); //updates turnVal

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = abs(turnVal) > abs(maxVal) ? maxVal * sgn(turnVal) : turnVal;
        runBase(leftVal, rightVal); //assigns values to the motors

        //if wanted, once the robot reaches a threshhold, it will continue for efficiency
        if(stopEarly && abs(turn.error) < 0.1)
            break;

        //debugging
        std::cout << "setPoint: " << setPoint << " | leftPos: " << -getLeftEnc() << " | rightPos: " << getRightEnc() << " | currentPos: " << (-getLeftEnc() + getRightEnc()) / 2 << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";

        delay(10);

    }

    runBase(0, 0); //stops the motors at the end

}

void curveBase(double leftPow, double rightPow, double fastSideDist) {
    //simple curving with constant voltage until a certain distance is achieved

    runBase(leftPow, rightPow);
    while(abs(getLeftEnc()) < abs(fastSideDist) && abs(getRightEnc()) < abs(fastSideDist))
        delay(10);
    runBase(0, 0);

}

void curveBaseVel(double maxLeftRPM, double maxRightRPM, double fastSideDist) {
    //curving using the built in velocity rpm and slew rate

    double maxAccel = 5;
    double leftRPM = 0, rightRPM = 0;
    //runs until a certain distance is achieved
    while(abs(getLeftEnc()) < abs(fastSideDist) && abs(getRightEnc()) < abs(fastSideDist)) {
        
        //proportionally updates the velocity of the right side if it's slower
        if(abs(maxLeftRPM) > abs(maxRightRPM)) {
            //if the goalRPM is reachable this turn, make the velocity the goalRPM
            if(abs(leftRPM) + abs(maxAccel) >= abs(maxLeftRPM)) {
                leftRPM = maxLeftRPM;
                rightRPM = maxRightRPM;
            }
            //otherwise increase the RPM of the motors proportionally
            else {
                leftRPM += maxAccel * sgn(maxLeftRPM);
                rightRPM += maxAccel * (maxRightRPM / maxLeftRPM) * sgn(maxRightRPM);
            }
        }

        //proportionally updates the velocity of the left side if it's slower
        else if(abs(maxRightRPM) > abs(maxLeftRPM)) {
            //if the goalRPM is reachable this turn, make the velocity the goalRPM
            if(abs(rightRPM) + abs(maxAccel) >= abs(maxRightRPM)) {
                leftRPM = maxLeftRPM;
                rightRPM = maxRightRPM;
            }
            //otherwise increase the RPM of the motors proportionally
            else {
                leftRPM += maxAccel * sgn(maxLeftRPM);
                rightRPM += maxAccel * (maxRightRPM / maxLeftRPM) * sgn(maxRightRPM);
            }
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