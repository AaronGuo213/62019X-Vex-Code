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

    //gets controller joystick values and translate them to the motors
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

    //returns the number of inches travelled by the left encoder wheel
    return leftEnc.get_value() * inchPerTickForward; 

}

double getRightEnc() {

    //returns the number of inches travelled by the right encoder wheel
    return rightEnc.get_value() * inchPerTickForward; 

}

void resetBaseEnc() {

    leftEnc.reset();
    rightEnc.reset();
    yawEnc.reset();

}

double getYawEnc() {

    //returns the number of inches travelled by the yaw encoder wheel
    return yawEnc.get_value() * inchPerTickYaw;

}