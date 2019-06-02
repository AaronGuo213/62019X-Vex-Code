#ifndef LIFT_H
#define LIFT_H

extern int potOffset;
void runLeftLift(float percentage);
void runRightLift(float percentage);
int getLiftHeight();
extern bool manual, manualUsed, shiftUp, shiftDown, reset;
extern int height, liftSetPoint;
extern int aboveCube[5];
void liftCtrl(void* param);
void autoAllign();
void autoStack();

#endif