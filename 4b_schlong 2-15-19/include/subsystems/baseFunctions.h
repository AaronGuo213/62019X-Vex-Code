#ifndef BASE_H
#define BASE_H

void moveStraight(double dist, bool stopEarly, int time, double maxVal = 100); //PID control loop for straight movement
void turn(double theta, bool stopEarly, int time, double maxVal = 100); //PID control loop for turning

#endif