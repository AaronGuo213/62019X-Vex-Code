#ifndef INTAKE_H
#define INTAKE_H

void runIntk(double percent);
void updateIntk();
void intkSafetyNet();

extern int intkTimer;
extern double intkPow;
void ctrlIntk(void *param);
void runIntk(double percent, int time);

#endif