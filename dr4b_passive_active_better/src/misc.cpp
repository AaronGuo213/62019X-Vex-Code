#include "main.h"

int sgn(float x) { //inputs a float and outputs its sign (+, -, or 0) as an int

    return (x > 0) - (x < 0);

}

PID initPID(bool useP, bool useI, bool useD, float kP, float kI, float kD) { //gives a created PID struct its values

    return { 0, 0, 0, 0, kP, kI, kD, useP, useI, useD };

}

float runPID(PID *pid) {

    pid->integral += pid->error; //increment integral by current error
    pid->derivative = pid->error - pid->prevError; //set derivative to the delta error
    pid->prevError = pid->error; //set prevError to current error to be used for next iteration
    return (pid->error * pid->kP * (float)pid->useP) + (pid->integral * pid->kI * (float)pid->useI) + (pid->derivative * pid->kD * (float)pid->useD); //calculate final value

}

float joyValRemap(float joyVal) {

    float percentVal;

    if((float)joyVal <= -3.0) { //threshold at 3/100 to prevent unwanted movement at low values

        percentVal = pow(-pow((float)joyVal, 2) - 6 * (float)joyVal + 18327.7, 0.5) - 154.414; //uses the equation of a circle to optimize slow and fast movements

    }

    else if((float)joyVal >= 3.0) { //threshold at 3/100 to prevent unwanted movement at low values

        percentVal = -pow(-pow((float)joyVal, 2) + 6 * (float)joyVal + 18327.7, 0.5) + 154.414; //uses the reflected equation to optimize slow and fast backwards movements

    }

    else {

        percentVal = 0.0;

    }

    return percentVal;

}

//buttons and joysticks

float lY() {
    return master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
}

float lX() {
    return master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
}

float rY() {
    return master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
}

float rX() {
    return master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
}

bool l1() {
    return master.get_digital(E_CONTROLLER_DIGITAL_L1);
}

bool l2() {
    return master.get_digital(E_CONTROLLER_DIGITAL_L2);
}

bool r1() {
    return master.get_digital(E_CONTROLLER_DIGITAL_R1);
}

bool r2() {
    return master.get_digital(E_CONTROLLER_DIGITAL_R2);
}