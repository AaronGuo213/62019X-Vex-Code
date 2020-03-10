#ifndef INTAKE_H
#define INTAKE_H

void runIntk(double percent);
void runIntkDist(double dist, double velocity);
void updateIntk();
void intkSafetyNet();
void brakeIntk();
void coastIntk();

struct intkQueue {
    double percent;
    int time;
};
void queueIntk(void* param);
void runIntk(double percent, int time);

#endif