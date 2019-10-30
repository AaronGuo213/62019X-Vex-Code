#include "main.h"

int sgn(double x) { //inputs a double and outputs its sign (+, -, or 0) as an int

    return (x > 0) - (x < 0);

}

PID initPID(bool useP, bool useI, bool useD, double kP, double kI, double kD) { //gives a created PID struct its values

    return { 0, 0, 0, 0, kP, kI, kD, useP, useI, useD };

}

double runPID(PID *pid) {

    pid->integral += pid->error;//pid->integrate ? pid->error : 0; //increment integral by current error
    pid->derivative = pid->error - pid->prevError; //set derivative to the delta error
    pid->prevError = pid->error; //set prevError to current error to be used for next iteration
    double output = (pid->error * pid->kP * (double)pid->useP) + (pid->integral * pid->kI * (double)pid->useI) + (pid->derivative * pid->kD * (double)pid->useD); //calculate final value
    return output;

}

double joyValRemap(double joyVal) {

    double percentVal;

    if((double)joyVal <= -3.0) { //threshold at 3/100 to prevent unwanted movement at low values

        percentVal = pow(-pow((double)joyVal, 2) - 6 * (double)joyVal + 18327.7, 0.5) - 154.414; //uses the equation of a circle to optimize slow and fast movements

    }

    else if((double)joyVal >= 3.0) { //threshold at 3/100 to prevent unwanted movement at low values

        percentVal = -pow(-pow((double)joyVal, 2) + 6 * (double)joyVal + 18327.7, 0.5) + 154.414; //uses the reflected equation to optimize slow and fast backwards movements

    }

    else {

        percentVal = 0.0;

    }

    return percentVal;

}

//buttons and joysticks

double lY() {
    return master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
}

double lX() {
    return master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
}

double rY() {
    return master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
}

double rX() {
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