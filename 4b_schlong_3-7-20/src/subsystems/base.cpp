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

    leftBase1.move_velocity(leftRPM); //runs the left and right base motors out of 200 rpm
    leftBase2.move_velocity(leftRPM);
    rightBase1.move_velocity(rightRPM);
    rightBase2.move_velocity(rightRPM);

}

void updateBase() {

    //gets controller joystick values
    double leftStickY = lY(), leftStickX = lX();
    double rightStickY = rY(), rightStickX = rX();

    //makes the base move forward when joysticks are close enough
    if(abs(leftStickY - rightStickY) < 10)
        leftStickY = rightStickY = (leftStickY + rightStickY) / 2;
    //converts joystick values to voltage percent and outputs to motors
    runBase(joyValRemap(leftStickY), joyValRemap(rightStickY));

    /*if(abs(leftStickX) < 50) { //arcade mode can be activated when the left stick is pushed to the side
        //makes the base move forward when joysticks are close enough
        if(abs(leftStickY - rightStickY) < 10)
            leftStickY = rightStickY = (leftStickY + rightStickY) / 2;
        //converts joystick values to voltage percent and outputs to motors
        runBase(joyValRemap(leftStickY), joyValRemap(rightStickY));
    }

    else {
        //arcade drive
        rightStickX = abs(rightStickX) > 20 ? rightStickX : 0;
        rightStickX *= rightStickY > 0 ? 1 : -1;
        leftStickY += rightStickX;
        rightStickY -= rightStickX;
        //converts joystick values to voltage percent and outputs to motors
        runBase(joyValRemap(leftStickY), joyValRemap(rightStickY));
    }*/

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

    //returns the number of inches travelled by the left encoder wheel
    return leftEnc.get_value() * inchPerTickForward; 

}

double getRightEnc() {

    //returns the number of inches travelled by the right encoder wheel
    return rightEnc.get_value() * inchPerTickForward; 

}

double getYawEnc() {

    //returns the number of inches travelled by the yaw encoder wheel
    return yawEnc.get_value() * inchPerTickYaw;

}

double getAngle() {

    //returns the global angle of the robot
    return -imu.get_yaw();

}

void resetBaseEnc() {

    leftEnc.reset();
    rightEnc.reset();
    yawEnc.reset();

}

void resetGyro() {

    imu.reset();

}

bool isBaseSettled() {

    int threshhold = 10;

    if(abs(leftBase1.get_actual_velocity()) > threshhold || abs(leftBase2.get_actual_velocity()) > threshhold)
        return false;

    if(abs(rightBase1.get_actual_velocity()) > threshhold || abs(rightBase2.get_actual_velocity()) > threshhold)
        return false;

    return true;

}

bool isBaseStopped() {

    if(leftBase1.get_actual_velocity() != 0 || leftBase2.get_actual_velocity() != 0)
        return false;

    if(rightBase1.get_actual_velocity() != 0 || rightBase2.get_actual_velocity() != 0)
        return false;

    return true;

}