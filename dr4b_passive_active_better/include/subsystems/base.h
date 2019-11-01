#ifndef BASE_H
#define BASE_H

void runLeftBase(double percent);
void runRightBase(double percent);
void updateBase();

double getLeftEnc();
double getRightEnc();
void resetBaseEnc();
double getYawEnc();
void resetYawEnc();

void moveStraight(double dist, int time, double maxVal = 90); //PID control loop for straight movement
void turn(double theta, int time, double maxVal = 100); //PID control loop for turning

#endif