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

    float theta;

    if(abs(x) > 0 || abs(y) > 0) {

        if(x == 0) {
            
            if(y >= 6)
                theta = 90;
            else if(y <= -6)
                theta = 270;

        }

        else if(y == 0) {

            if(x >= 6)
                theta = 0;
            if(x <= -6)
                theta = 180;

        }

        else if(x > 0) {
            
            theta = atan(y / x) * 180 / M_PI;

        }

        else if(x < 0) {

            theta = atan(y / x) * 180 / M_PI + 180;

        }

    }

    else
        theta = 0;

    return theta;

}


float joyValRemap(float joyVal) {

    float percentVal = 0.0;

    if((float)joyVal <= -3.0) {

        percentVal = pow(-pow((float)joyVal, 2) - 6 * (float)joyVal + 18327.7, 0.5) - 154.414;

    }

    else if((float)joyVal >= 3.0) {

        percentVal = -pow(-pow((float)joyVal, 2) + 6 * (float)joyVal + 18327.7, 0.5) + 154.414;

    }

    else {

        percentVal = 0.0;

    }

    return percentVal;

}