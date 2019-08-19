#ifndef LIFT_H
#define LIFT_H

extern int clawCount, clawPercent;
void runClaw(float percent, int time);
void clawCtrl(void* param);

void runLeftLift(float percent);
void runRightLift(float percent);
int getLiftHeight();
extern int liftSetPoint;
extern bool ctrlLift, slowHold;
extern int aboveCube[5];
void liftCtrl(void* param);

#endif