#include "main.h"

void runBase(double leftPercent, double rightPercent) { //values -100 to 100

    leftBase1.move_voltage(leftPercent * 120); //runs the left base motors out of 12000mV
    leftBase2.move_voltage(leftPercent * 120);
    rightBase1.move_voltage(rightPercent * 120); //runs the right base motors out of 12000mV
    rightBase2.move_voltage(rightPercent * 120);

}

void runBase(double percent) { //values -100 to 100

    leftBase1.move_voltage(percent * 120); //runs the base motors out of 12000mV
    leftBase2.move_voltage(percent * 120);
    rightBase1.move_voltage(percent * 120);
    rightBase2.move_voltage(percent * 120);

}

void runBaseVel(double leftRPM, double rightRPM) { //values -200 to 200

    leftBase1.move_velocity(leftRPM); //runs the base motors out of 200 rpm
    leftBase2.move_velocity(leftRPM);
    rightBase1.move_velocity(rightRPM);
    rightBase2.move_velocity(rightRPM);

}

void updateBase() {

    //uses joystick values to run the base
    runBase(joyValRemap(lY()), joyValRemap(rY()));

    //checks for overheating
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
const double inchPerTickYaw = 0.02440678;

double getLeftEnc() {

    //returns the number of inches traveled by the left encoder wheel
    return leftEnc.get_value() * inchPerTickForward; 

}

double getRightEnc() {

    //returns the number of inches traveled by the right encoder wheel
    return rightEnc.get_value() * inchPerTickForward; 

}

double getLeftEncMotors() {

    //motor encoder values
    return (leftBase1.get_position() + leftBase2.get_position()) / 2;

}

double getRightEncMotors() {

    //motor encoder values
    return (rightBase1.get_position() + rightBase2.get_position()) / 2;

}

double getYawEnc() {

    //returns the number of inches travelled by the yaw encoder wheel
    return yawEnc.get_value() * inchPerTickYaw;

}

double getAngle() {

    //returns the global angle of the robot
    return -imu.get_yaw() - startingZero;

}

double startingZero; //offset of the gyro

void resetEnc() {

    leftEnc.reset();
    rightEnc.reset();
    yawEnc.reset();

}

void resetBaseMotorEnc() {

    leftBase1.tare_position();
    leftBase2.tare_position();
    rightBase1.tare_position();
    rightBase2.tare_position();

}

void resetGyro() {

    imu.reset();

}

double getSonarInches(int numTimes) {

    double rtn = 0;
    for(int i = 0; i < numTimes; i++) { //averages a bunch of recordings in case of outliers
        rtn += sonar.get_value() * 0.0393701; //converts from mm to inches
        delay(10);
    }
    return rtn / numTimes;

}

bool isBaseSettled(int rpmThreshhold) { //determines if the base is slowed/stopped

    if(abs(leftBase1.get_actual_velocity()) > rpmThreshhold || abs(leftBase2.get_actual_velocity()) > rpmThreshhold)
        return false;

    if(abs(rightBase1.get_actual_velocity()) > rpmThreshhold || abs(rightBase2.get_actual_velocity()) > rpmThreshhold)
        return false;

    return true;

}