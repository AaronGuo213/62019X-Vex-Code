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