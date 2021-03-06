#ifndef INTAKE_H
#define INTAKE_H

void runIntk(double percent);
void runIntkDist(double dist, double velocity);
void updateIntk();
void intkSafetyNet();
void brakeIntk();
void coastIntk();

extern int intkTimer;
extern double intkPow;
void ctrlIntk(void *param);
void runIntk(double percent, int time);

#endif