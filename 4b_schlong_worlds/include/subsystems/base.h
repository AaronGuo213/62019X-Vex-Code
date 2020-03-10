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
double getLeftEncMotors();
double getRightEncMotors();
double getYawEnc();
double getAngle();
extern double startingZero;
void resetEnc();
void resetBaseMotorEnc();
void resetGyro();
double getSonarInches(int numTimes = 1);
bool isBaseSettled(int rpmThreshhold = 5);

#endif