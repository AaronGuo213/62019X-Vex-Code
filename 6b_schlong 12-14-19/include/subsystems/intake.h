#ifndef INTAKE_H
#define INTAKE_H

void runIntk(double percent);
void updateIntk();

void runTray(double percent);
int getTrayPos();
double calcTrayPow(bool isOuttaking);
void updateTray();

void outtake(double intkSpeed = 0);

enum class trayStatus {idle, hold, outtake, retract};
extern trayStatus trayStat;
void trayCtrl(void* param);

#endif