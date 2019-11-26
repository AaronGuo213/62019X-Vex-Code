#include "main.h"

int sgn(float x) { //inputs a double and outputs its sign (+ or -) as an int

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

float findTheta(float x, float y) {

    return atan2(y, x) * 180 / 3.1415926535; //returns the angle of the joystick in degrees

}


float joyValRemap(float joyVal) {

    float percentVal = 0.0;

    if((float)joyVal <= -3.0) { //threshold prevents accidental movement at low values

        percentVal = pow(-pow((float)joyVal, 2) - 6 * (float)joyVal + 18327.7, 0.5) - 154.414; //uses a circle to maximize the versatility of slow movement and still allow for fast movement

    }

    else if((float)joyVal >= 3.0) {

        percentVal = -pow(-pow((float)joyVal, 2) + 6 * (float)joyVal + 18327.7, 0.5) + 154.414; //uses the same circle but negated

    }

    else {

        percentVal = 0.0;

    }

    return percentVal;

}