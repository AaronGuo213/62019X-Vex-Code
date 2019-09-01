#ifndef BASE_H
#define BASE_H

void runLeftBase(float percent);
void runRightBase(float percent);
float getLeftEnc();
float getRightEnc();
void resetBaseEnc();
float getYawEnc();
void resetYawEnc();

void moveStraight(float dist, int time, float maxVal); //PID control loop for straight movement
void turn(float theta, int time); //PID control loop for turning

#endif