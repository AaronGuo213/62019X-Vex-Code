#ifndef INTAKE_H
#define INTAKE_H

void runLift(float percentage);
void runClaw(float percentage);
extern bool manual, manualUsed, shiftUp, shiftDown, reset;
extern int height, liftSetPoint;
extern int aboveCube[5];
void liftCtrl(void* param);
void autostack(int cubes);

#endif