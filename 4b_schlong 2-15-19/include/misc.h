#ifndef MISC_H
#define MISC_H

extern const double PI;
int sgn(double x); //inputs a double and outputs its sign (+ or -) as an int
double joyValRemap(double joyVal); //optimizes the slow and fast motor values during driver control
double speedToVolt(double speed);

struct PID { //a holder for multiple values used in PID
    double error, integral, derivative, prevError, kP, kI, kD; //PID variables and constants
    bool useP, useI, useD; //0 to disable certain terms, 1 to enable
};
PID initPID(bool useP, bool useI, bool useD, double kP, double kI, double kD); //gives a created PID struct its values
double runPID(PID *pid); //inputs a PID struct, does the actual PID math, then outputs a double

//buttons and joysticks
double lY();
double lX();
double rY();
double rX();
bool l1(bool newPress = false);
bool l2(bool newPress = false);
bool r1(bool newPress = false);
bool r2(bool newPress = false);

#endif