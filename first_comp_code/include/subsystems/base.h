#ifndef BASE_H
#define BASE_H

void runLeftBase(float leftBaseVal);
void runRightBase(float rightBaseVal);

float leftBaseRemap(float r, float theta);
float rightBaseRemap(float r, float theta);

float getForwardEnc();
float getYawEnc();
void resetLeftEnc();
void resetRightEnc();
void resetYawEnc();
void resetEnc();

void moveStraight(float dist, float theta, int time);

#endif