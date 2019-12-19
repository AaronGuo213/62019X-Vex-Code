#ifndef BASICS_H
#define BASICS_H

void runBase(double leftPercent, double rightPercent);
void runBaseVel(double leftRPM, double rightRPM);
void updateBase();
void baseSafetyNet();
extern const double inchPerTickForward;
extern const double inchPerTickYaw;
double getLeftEnc();
double getRightEnc();
void resetBaseEnc();
double getYawEnc();

#endif