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

const double inchPerTickForward = 0;
const double inchPerTickYaw = 0;

double getLeftEnc() {

    //averages the left base motor encoder values
    return (leftBase1.get_position() + leftBase2.get_position()) / 2; //* inchPerTickForward; 

}

double getRightEnc() {

    //averages the right base motor encoder values
    return (rightBase1.get_position() + rightBase2.get_position()) / 2; //* inchPerTickForward; 

}

void resetBaseEnc() {

    leftBase1.tare_position();
    leftBase2.tare_position();
    rightBase1.tare_position();
    rightBase2.tare_position();

}

double getYawEnc() {

    return yawEnc.get_value();// * inchPerTickYaw;

}

void resetYawEnc() {

    yawEnc.reset();

}

void moveStraight(double distance, int time, double maxVal) { //PID control loop to move the base to a certain relative 
                                                            //postition with minimal forwards and sideways error

    double distVal, diffVal, leftVal, rightVal;
    PID dist = initPID(1, 1, 1, 0.4, 0.00005, 0.8); //kP = 0.4, kI = 0.00005, kD = 0.8
    PID diff = initPID(1, 0, 0, 0.1, 0, 0); //kP = 0.1

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        dist.error = distance - ((getLeftEnc() + getRightEnc()) / 2); //updates error for distance PID
        diff.error = (getLeftEnc() - getRightEnc()) / 2; //updates error for difference PID
        distVal = runPID(&dist); //updates distVal
        diffVal = runPID(&diff); //updates diffVal
        
        //limits the values before sending them to the motors
        //distVal = distVal > 90 ? 90 : distVal; //limits distVal to 90 in order to allow diffVal to have an effect
        diffVal = dist.error < 100 ? diffVal * 0.1 : diffVal; //limits the influence of the diffVal when near the setpoint
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

void turn(double units, int time, double maxVal) { //PID control loop to turn a desired angle with minimal angle error

    double setPoint = units * 10; //makes the input more friendly numbers
    double turnVal, dispVal;
    double leftVal, rightVal;
    PID turn = initPID(1, 1, 1, 0.19, 0.0001, 0.8); //kP = 0.19, kI = 0.0001, kD = 0.8;
    PID disp = initPID(0, 0, 0, 0, 0, 0); //disp PID not active

    resetBaseEnc();
    resetYawEnc();

    for(int i = 0; i < time; i+=10) { //updates every 10 ms

        turn.error = setPoint - getYawEnc(); //updates error for turn PID
        disp.error = (getLeftEnc() + getRightEnc()) / 4; //updates error for displacement PID
        turnVal = runPID(&turn); //updates turnVal
        dispVal = runPID(&disp); //updates dispVal

        //limits the values before sending them to the motors
        leftVal = -turnVal - dispVal;
        leftVal = abs(leftVal) > abs(maxVal) ? maxVal * sgn(leftVal) : leftVal;
        rightVal = turnVal - dispVal;
        rightVal = abs(rightVal) > abs(maxVal) ? maxVal * sgn(rightVal) : rightVal;
        runLeftBase(leftVal); //assigns values to the motors
        runRightBase(rightVal);

        std::cout << "setPoint: " << setPoint << " | currentPos: " << getYawEnc() << " | error: " << turn.error << " | turnVal: " << turnVal << " | dispError: " << disp.error << " | dispVal: " << dispVal << " | time: " << i << "\n";

        delay(10);

    }

    runLeftBase(0); //stops the motors at the end
    runRightBase(0);

}

void moveCurved(double radius, double angle, int time, double maxVal) {

    double leftSetPoint = (radius - 4) * (angle * M_PI / 180) / (3.25 * M_PI) * 360;
    double rightSetPoint = (radius + 4) * (angle * M_PI / 180) / (3.25 * M_PI) * 360;
    double ratio = abs(leftSetPoint) > abs(rightSetPoint) ? rightSetPoint / leftSetPoint : leftSetPoint / rightSetPoint;
    PID dist = initPID(1, 1, 1, 0.4, 0.00005, 0.8); //kP = 0.4, kI = 0.00005, kD = 0.8
    PID diff = initPID(1, 0, 0, 0.1, 0, 0); //kP = 0.1
    double distVal, diffVal, leftVal, rightVal;
    resetBaseEnc();
    resetYawEnc();

    if(leftSetPoint > rightSetPoint) {

        for(int i = 0; i < time; i+=10) { //updates every 10 ms

            dist.error = leftSetPoint - getLeftEnc();
            diff.error = (getLeftEnc() - (getRightEnc() * ratio)) / 2; //updates error for difference PID
            distVal = runPID(&dist); //updates distVal
            diffVal = runPID(&diff); //updates diffVal
            
            //limits the values before sending them to the motors
            distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
            leftVal = distVal - diffVal;
            rightVal = (distVal * ratio) + diffVal;

            leftBase1.move_velocity(leftVal); //assigns the values to the motors
            leftBase2.move_velocity(leftVal);
            rightBase1.move_velocity(rightVal);
            rightBase2.move_velocity(rightVal);

            delay(10);

        }
        runLeftBase(0); //stops the motors
        runRightBase(0);

    }

    else {

        for(int i = 0; i < time; i+=10) { //updates every 10 ms

            dist.error = rightSetPoint - getRightEnc();
            diff.error = ((getLeftEnc() * ratio) - getRightEnc()) / 2; //updates error for difference PID
            distVal = runPID(&dist); //updates distVal
            diffVal = runPID(&diff); //updates diffVal
            
            //limits the values before sending them to the motors
            distVal = abs(distVal) > abs(maxVal) ? maxVal * sgn(distVal) : distVal;
            leftVal = (distVal * ratio) - diffVal;
            rightVal = distVal * ratio + diffVal;

            leftBase1.move_velocity(leftVal); //assigns the values to the motors
            leftBase2.move_velocity(leftVal);
            rightBase1.move_velocity(rightVal);
            rightBase2.move_velocity(rightVal);

            delay(10);

        }
        runLeftBase(0); //stops the motors
        runRightBase(0);

    }

}