#ifndef BASE_H
#define BASE_H

void runLeftBase(float percent);
void runRightBase(float percent);

float getLeftEnc();
float getRightEnc();
void resetBaseEnc();

float getYawEnc();
void resetYawEnc();

void moveStraight(float dist, int time);
void turn(float theta, int time);

#endif