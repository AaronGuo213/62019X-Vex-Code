#include "main.h"

void runLeftBase(double percent) {

    leftBase1.move_voltage(percent * 120); //runs the left base motors out of 12000mV
    leftBase2.move_voltage(percent * 120);

}

void runRightBase(double percent) {

    rightBase1.move_voltage(percent * 120); //runs the right base motors out of 12000mV
    rightBase2.move_voltage(percent * 120);

}

void updateBase() {

    runLeftBase(joyValRemap(lY()));
    runRightBase(joyValRemap(rY()));

    //prevents the motors from overheating and breaking
    if(leftLift.is_over_temp())
        leftLift.set_voltage_limit(0);
    else
        leftLift.set_voltage_limit(12000);

    if(rightLift.is_over_temp())
        rightLift.set_voltage_limit(0);
    else
        rightLift.set_voltage_limit(12000);

}

double getLeftEnc() {

    return (leftBase1.get_position() + leftBase2.get_position()) / 2; 
    //averages the left base motor encoder values

}

double getRightEnc() {

    return (rightBase1.get_position() + rightBase2.get_position()) / 2; 
    //averages the right base motor encoder values

}

void resetBaseEnc() {

    leftBase1.tare_position();
    leftBase2.tare_position();
    rightBase1.tare_position();
    rightBase2.tare_position();

}

double getYawEnc() {

    return yawEnc.get_value();

}

void resetYawEnc() {

    yawEnc.reset();

}

void moveStraight(double distance, int time, double maxVal) { //PID control loop to move the base to a certain relative 
                                                            //postition with minimal forwards and sideways error

    distance *= 17.4; //makes the input distance 48 exactly equal to one tile length, distance 11 exactly equal to one cube length
    double distVal, diffVal, leftVal, rightVal;
    PID dist = initPID(1, 0, 1, 0.75, 0, 0.6); //kP = 0.75, kD = 0.6
    PID diff = initPID(1, 0, 0, 0.5, 0, 0); //kP = 0.5

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        dist.error = distance - ((getLeftEnc() + getRightEnc()) / 2); //updates error for distance PID
        diff.error = (getLeftEnc() - getRightEnc()) / 2; //updates error for difference PID
        distVal = runPID(&dist); //updates distVal, reference misc.cpp
        distVal = distVal > 90 ? 90 : distVal; //limits distVal to 90 in order to allow diffVal to make and impact
        diffVal = runPID(&diff); //updates diffVal, reference misc.cpp
        
        //limits the values before sending them to the motors
        diffVal = dist.error < 100 ? diffVal * 0.1 : diffVal; //limits the influence of the diffVal when near the setpoint
        leftVal = distVal - diffVal;
        leftVal = abs(leftVal) > abs(maxVal) ? maxVal * sgn(leftVal) : leftVal;
        rightVal = distVal + diffVal;
        rightVal = abs(rightVal) > abs(maxVal) ? maxVal * sgn(rightVal) : rightVal;

        runLeftBase(leftVal);
        runRightBase(rightVal);

        std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors at the end
    runRightBase(0);

}

/*void moveStraightLimited(double distance, int time, double maxVal, double maxAccel) { //PID control loop to move the base to a certain relative 
                                                            //postition with minimal forwards and sideways error

    distance *= 17.4; //makes the input distance 48 exactly equal to one tile length, distance 11 exactly equal to one cube length
    double distVal, diffVal, leftVal, rightVal;
    double prevLeftVal = 0, prevRightVal = 0;
    PID dist = initPID(1, 0, 1, 0.75, 0, 0.6); //kP = 0.75, kD = 0.6
    PID diff = initPID(1, 0, 0, 0.5, 0, 0); //kP = 0.5

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        dist.error = distance - ((getLeftEnc() + getRightEnc()) / 2); //updates error for distance PID
        diff.error = (getLeftEnc() - getRightEnc()) / 2; //updates error for difference PID
        distVal = runPID(&dist); //updates distVal, reference misc.cpp
        distVal = distVal > 90 ? 90 : distVal; //limits distVal to 90 in order to allow diffVal to make and impact
        diffVal = runPID(&diff); //updates diffVal, reference misc.cpp
        
        //limits the values before sending them to the motors
        diffVal = dist.error < 100 ? diffVal * 0.1 : diffVal; //limits the influence of the diffVal when near the setpoint
        leftVal = distVal - diffVal;
        leftVal = abs(leftVal) > abs(maxVal) ? maxVal * sgn(leftVal) : leftVal;
        rightVal = distVal + diffVal;
        rightVal = abs(rightVal) > abs(maxVal) ? maxVal * sgn(rightVal) : rightVal;

        if(maxAccel) {
            leftVal = prevLeftVal - leftVal > maxAccel ? prevLeftVal - maxAccel : leftVal;
            leftVal = leftVal - prevLeftVal > maxAccel ? prevLeftVal + maxAccel : leftVal;
            rightVal = prevRightVal - rightVal > maxAccel ? prevRightVal - maxAccel : rightVal;
            rightVal = rightVal - prevRightVal > maxAccel ? prevRightVal + maxAccel : rightVal;
            prevLeftVal = leftVal;
            prevRightVal = rightVal;
        }

        runLeftBase(leftVal);
        runRightBase(rightVal);

        std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";


        delay(10);

    }

    runLeftBase(0); //stops the motors at the end
    runRightBase(0);

}*/

void turn(double theta, int time, double maxVal) { //PID control loop to turn a desired angle with minimal angle error

    double setPoint = theta * 3.1; //adjusts the angle to fit with the encoder values
    double turnVal, dispVal;
    double leftVal, rightVal;
    PID turn = initPID(1, 0, 1, 0.8, 0, 0.6); //kP = 0.8, kD = 0.6;
    PID disp = initPID(0, 0, 0, 0, 0, 0); //disp PID not active

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        turn.error = setPoint - (getRightEnc() - getLeftEnc()) / 2; //updates error for turn PID
        disp.error = (getLeftEnc() + getRightEnc()) / 4; //updates error for displacement PID
        turnVal = runPID(&turn); //updates turnVal, reference misc.cpp
        dispVal = runPID(&disp); //updates dispVal, reference misc.cpp

        //limits the values before sending them to the motors
        leftVal = -turnVal - dispVal;
        leftVal = abs(leftVal) > abs(maxVal) ? maxVal * sgn(leftVal) : leftVal;
        rightVal = turnVal - dispVal;
        rightVal = abs(rightVal) > abs(maxVal) ? maxVal * sgn(rightVal) : rightVal;
        runLeftBase(leftVal);
        runRightBase(rightVal);

        std::cout << "setPoint: " << setPoint << " | currentPos: " << (getRightEnc() - getLeftEnc()) / 2 << " | error: " << turn.error << " | turnVal: " << turnVal << " | dispError: " << disp.error << " | dispVal: " << dispVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors at the end
    runRightBase(0);

}