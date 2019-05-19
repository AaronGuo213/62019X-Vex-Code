#ifndef LIFT_H
#define LIFT_H

void runLift(float percentage);
extern bool manual, manualUsed, shiftUp, shiftDown, reset;
void liftCtrl(void* param);
//void shiftLift(int direction);

#endif