#ifndef MISC_H
#define MISC_H
#define M_PI 3.1415926535

int sgn(double x); //inputs a double and outputs its sign (+ or -) as an int
struct PID { //a holder for multiple values used in PID
    double error, integral, derivative, prevError, kP, kI, kD; //PID variables and constants
    bool useP, useI, useD; //0 to disable certain terms, 1 to enable
};
PID initPID(bool useP, bool useI, bool useD, double kP, double kI, double kD); //gives a created PID struct its values
double runPID(PID *pid); //inputs a PID struct, does the actual PID math, then outputs a double

double joyValRemap(double joyVal); //optimizes the slow and fast motor values during driver control

//buttons and joysticks
double lY();
double lX();
double rY();
double rX();
bool l1();
bool l2();
bool r1();
bool r2();

#endif