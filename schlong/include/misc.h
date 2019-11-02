#ifndef MISC_H
#define MISC_H

int sgn(float x); //inputs a double and outputs its sign (+ or -) as an int
struct PID { //a holder for multiple values used in PID
    float error, integral, derivative, prevError, kP, kI, kD; //PID variables and constants
    bool useP, useI, useD; //0 to disable certain terms, 1 to enable
};
PID initPID(bool useP, bool useI, bool useD, float kP, float kI, float kD); //gives a created PID struct its values
float runPID(PID *pid); //inputs a PID struct, does the actual PID math, then outputs a double

float joyValRemap(float joyVal);

#endif