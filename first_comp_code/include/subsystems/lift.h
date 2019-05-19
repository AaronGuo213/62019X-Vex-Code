#ifndef LIFT_H
#define LIFT_H

void runLift(float percentage);
extern bool manual, manualUsed, shiftUp, shiftDown, reset;
extern int height, setPoint;
void liftCtrl(void* param);
//void shiftLift(int direction);

#endif