#ifndef BASE_H
#define BASE_H

void runLeftBase1(float percentage);
void runLeftBase2(float percentage);
void runRightBase1(float percentage);
void runRightBase2(float percentage);

float leftBaseRemap(float r, float theta);
float rightBaseRemap(float r, float theta);

float getBaseMotorEnc();
float getForwardEnc();
float getYawEnc();
void resetLeftEnc();
void resetRightEnc();
void resetYawEnc();
void resetBaseMotorEnc();
void resetEnc();

void moveStraight(float dist, float theta, int time);
void turn(float theta, int time);

#endif