#ifndef INTAKE_H
#define INTAKE_H

void runIntk(double percent);
void updateIntk();

void runTray(double percent);
int getTrayPos();
void updateTray();

void outtake(double intkSpeed = 0);

#endif