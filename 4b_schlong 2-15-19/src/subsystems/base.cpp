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

    //gets controller joystick values and translate them to the motors
    runLeftBase(joyValRemap(lY()));
    runRightBase(joyValRemap(rY()));
    baseSafetyNet();

}

void baseSafetyNet() {

    //prevents the motors from overheating and breaking
    if(leftBase1.is_over_temp())
        leftBase1.set_voltage_limit(0);
    else
        leftBase1.set_voltage_limit(12000);

    if(leftBase2.is_over_temp())
        leftBase2.set_voltage_limit(0);
    else
        leftBase2.set_voltage_limit(12000);

    if(rightBase1.is_over_temp())
        rightBase1.set_voltage_limit(0);
    else
        rightBase1.set_voltage_limit(12000);

    if(rightBase2.is_over_temp())
        rightBase2.set_voltage_limit(0);
    else
        rightBase2.set_voltage_limit(12000);

}

const double inchPerTickForward = 0.02440678; //1475 ticks over 36 inches
const double inchPerTickYaw = 0;

double getLeftEnc() {

    //averages the left base motor encoder values
    return leftEnc.get_value() * inchPerTickForward; 

}

double getRightEnc() {

    //averages the right base motor encoder values
    return rightEnc.get_value() * inchPerTickForward; 

}

void resetBaseEnc() {

    leftEnc.reset();
    rightEnc.reset();

}

double getYawEnc() {

    return yawEnc.get_value() * inchPerTickYaw;

}

void resetYawEnc() {

    yawEnc.reset();

}

void moveStraightTimed(double distance, int time, double maxVal) { //PID control loop to move the base to a certain relative 
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

        runLeftBase(leftVal); //assigns the values to the motors
        runRightBase(rightVal);

        std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors
    runRightBase(0);

}

void turnTimed(double setPoint, int time, double maxVal) { //PID control loop to turn a desired angle with minimal angle error

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

        std::cout << "setPoint: " << setPoint << " | currentPos: " << (-getLeftEnc() + getRightEnc()) / 2 << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors at the end
    runRightBase(0);

}

void moveStraight(double distance, int time, double maxVal) { //PID control loop to move the base to a certain relative 
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

        if(abs(dist.error) < 0.2)
            break;

        runLeftBase(leftVal); //assigns the values to the motors
        runRightBase(rightVal);

        std::cout << "setPoint: " << distance << " | currentPos: " << (getLeftEnc() + getRightEnc()) / 2 << " | error: " << dist.error << " | distVal: " << distVal << " | diffError: " << diff.error << " | diffVal: " << diffVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors
    runRightBase(0);

}

void turn(double setPoint, int time, double maxVal) { //PID control loop to turn a desired angle with minimal angle error

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

        if(abs(turn.error) < 0.1)
            break;

        std::cout << "setPoint: " << setPoint << " | leftPos: " << -getLeftEnc() << " | rightPos: " << getRightEnc() << " | currentPos: " << (-getLeftEnc() + getRightEnc()) / 2 << " | error: " << turn.error << " | turnVal: " << turnVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors at the end
    runRightBase(0);

}

void moveCurved(double radius, double angle, int time, double maxVal) {

    const double robotRadius = 0;
    double rightDist = angle * (radius + robotRadius);
    double leftDist = angle * (radius - robotRadius);
    if(leftDist > rightDist) {
        leftBase1.move_relative(leftDist / inchPerTickForward, maxVal * 2);
        leftBase2.move_relative(leftDist / inchPerTickForward, maxVal * 2);
        rightBase1.move_relative(rightDist / inchPerTickForward, maxVal * 2 * rightDist / leftDist);
        rightBase2.move_relative(rightDist / inchPerTickForward, maxVal * 2 * rightDist / leftDist);
    }
    else {
        leftBase1.move_relative(leftDist / inchPerTickForward, maxVal * 2 * leftDist / rightDist);
        leftBase2.move_relative(leftDist / inchPerTickForward, maxVal * 2 * leftDist / rightDist);
        rightBase1.move_relative(rightDist / inchPerTickForward, maxVal * 2);
        rightBase2.move_relative(rightDist / inchPerTickForward, maxVal * 2);
    }
    delay(time);

}