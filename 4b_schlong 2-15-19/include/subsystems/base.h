#ifndef BASICS_H
#define BASICS_H

void runLeftBase(double percent);
void runRightBase(double percent);
void updateBase();
void baseSafetyNet();
extern const double inchPerTickForward;
extern const double inchPerTickYaw;
double getLeftEnc();
double getRightEnc();
void resetBaseEnc();
double getYawEnc();
void resetYawEnc();

#endif