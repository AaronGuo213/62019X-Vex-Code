#ifndef BASE_H
#define BASE_H

void runWestBase(float westBaseVal);
void runEastBase(float eastBaseVal);

float westBaseRemap(float r, float theta);
float eastBaseRemap(float r, float theta);

float getLeftEnc();
float getRightEnc();
void resetLeftEnc();
void resetRightEnc();

#endif