#ifndef BASE_H
#define BASE_H

void runLeftBase(float percentage);
void runRightBase(float percentage);

float getBaseEnc();
float getLeftBaseEnc();
float getRightBaseEnc();
void resetBaseEnc();

float getForeEnc();
float getYawEnc();
void resetEnc();

void moveStraight(float dist, int time);
void turn(float theta, int time);

#endif