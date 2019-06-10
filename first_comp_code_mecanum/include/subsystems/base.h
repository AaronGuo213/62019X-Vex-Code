#ifndef BASE_H
#define BASE_H

void runLeftBase1(float percentage);
void runLeftBase2(float percentage);
void runRightBase1(float percentage);
void runRightBase2(float percentage);

float getBaseEnc();
float getLeftBaseEnc();
float getRightBaseEnc();
void resetBaseEnc();

float getYawEnc();
void resetYawEnc();

void moveStraight(float dist, int time);
void turn(float theta, int time);

#endif