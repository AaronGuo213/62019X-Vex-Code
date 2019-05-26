#ifndef INTAKE_H
#define INTAKE_H

void runClaw(float percentage, int time);
extern float clawVal;
extern int runTime;
void clawCtrl(void* param);

#endif