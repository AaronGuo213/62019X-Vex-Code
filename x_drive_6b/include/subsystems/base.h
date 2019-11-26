#ifndef BASE_H
#define BASE_H

void runLeftBase1(float percentage);
void runLeftBase2(float percentage);
void runRightBase1(float percentage);
void runRightBase2(float percentage);

float leftBaseRemap(float r, float theta);
float rightBaseRemap(float r, float theta);

float getBaseMotorEnc();
float getLeftBaseEnc();
float getRightBaseEnc();
void resetBaseMotorEnc();

float getAftEnc();
float getYawEnc();
void resetAftEnc();
void resetYawEnc();
void resetEnc();

void moveStraightEnc(float dist, float theta, int time);
void moveStraight(float dist, float theta, int time);
void turn(float theta, int time);

#endif