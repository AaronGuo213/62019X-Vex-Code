#ifndef BASICS_H
#define BASICS_H

void runBase(double leftPercent, double rightPercent);
void runBase(double percent);
void runBaseVel(double leftRPM, double rightRPM);
void updateBase();
void baseSafetyNet();
extern const double inchPerTickForward;
extern const double inchPerTickYaw;
double getLeftEnc();
double getRightEnc();
double getYawEnc();
void resetBaseEnc();
bool isBaseSettled();
bool isBaseStopped();

#endif