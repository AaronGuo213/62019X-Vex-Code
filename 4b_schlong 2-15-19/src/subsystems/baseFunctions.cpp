#include "main.h"

void moveStraight(double distance, bool stopEarly, int time, double maxVal) { //PID control loop to move the base to a certain relative 
                                                            //postition with minimal forwards and sideways error

    double distVal, diffVal, leftVal, rightVal;
    PID dist = initPID(1, 1, 1, 9, 0.004, 10); //kP = 9, kI = 0.004, kD = 10
    PID diff = initPID(1, 0, 0, 200, 0, 0); //kP = 200

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        dist.error = distance - ((getLeftEnc() + getRightEnc()) / 2); //updates error for distance PID
        diff.error = (getLeftEnc() - getRightEnc()) / 2; //updates error for difference PID
        distVal = runPID(&dist); //updates distVal
        diffVal = runPID(&diff); //updates diffVal
        
        //limits the values before sending them to the motors
        //distVal = distVal > 90 ? 90 : distVal; //limits distVal to 90 in order to allow diffVal to have an effect
        diffVal = abs(dist.error) < 100 ? diffVal * 0.1 : diffVal; //limits the influence of the diffVal when near the setpoint
        distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
        leftVal = distVal - diffVal;
        rightVal = distVal + diffVal;

        if(stopEarly && abs(dist.error) < 0.2)
            break;

        runLeftBase(leftVal); //assigns the values to the motors
        runRightBase(rightVal);

        std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors
    runRightBase(0);

}

void turn(double setPoint, bool stopEarly, int time, double maxVal) { //PID control loop to turn a desired angle with minimal angle error

    double turnVal;
    double leftVal, rightVal;
    PID turn = initPID(1, 0, 1, 35, 0.00004, 200); //kP = 0.19, kI = 0.0001, kD = 0.8;

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        turn.error = setPoint - ((-getLeftEnc() + getRightEnc()) / 2); //updates error for turn PID
        turnVal = runPID(&turn); //updates turnVal

        //limits the values before sending them to the motors
        leftVal = abs(-turnVal) > abs(maxVal) ? maxVal * sgn(-turnVal) : -turnVal;
        rightVal = abs(turnVal) > abs(maxVal) ? maxVal * sgn(turnVal) : turnVal;
        runLeftBase(leftVal); //assigns values to the motors
        runRightBase(rightVal);

        if(stopEarly && abs(turn.error) < 0.1)
            break;

        std::cout << "setPoint: " << setPoint << " | leftPos: " << -getLeftEnc() << " | rightPos: " << getRightEnc() << " | currentPos: " << (-getLeftEnc() + getRightEnc()) / 2 << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors at the end
    runRightBase(0);

}