#ifndef LIFT_H
#define LIFT_H

void runLeftLift(float percent);
void runRightLift(float percent);
int getLiftHeight();
int getLiftSpeed();
extern int liftSetPoint;
extern bool holdLift, slowLift, stack;
extern bool resetPID;
extern int slowTimer;
void liftCtrl(void* param); //slows and holds lift on queues

#endif