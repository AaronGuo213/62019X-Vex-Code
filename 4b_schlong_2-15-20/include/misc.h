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
double lY(Controller cont = master);
double lX(Controller cont = master);
double rY(Controller cont = master);
double rX(Controller cont = master);
bool l1Pressed(Controller cont = master, bool newPress = false);
bool l2Pressed(Controller cont = master, bool newPress = false);
bool r1Pressed(Controller cont = master, bool newPress = false);
bool r2Pressed(Controller cont = master, bool newPress = false);
bool upPressed(Controller cont = master, bool newPress = false);
bool downPressed(Controller cont = master, bool newPress = false);
bool leftPressed(Controller cont = master, bool newPress = false);
bool rightPressed(Controller cont = master, bool newPress = false);
bool aPressed(Controller cont = master, bool newPress = false);
bool bPressed(Controller cont = master, bool newPress = false);
bool xPressed(Controller cont = master, bool newPress = false);
bool yPressed(Controller cont = master, bool newPress = false);

#endif