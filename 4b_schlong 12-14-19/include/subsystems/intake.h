#ifndef INTAKE_H
#define INTAKE_H

void runIntk(double percent);
void updateIntk();
void intkSafetyNet();

void runTray(double percent);
int getTrayPos();
double calcTrayPow(bool isOuttaking);
void updateTray();
void traySafetyNet();

void outtake(double intkSpeed = 0);

extern double traySetPoint;
extern bool resetTrayIntegral;
enum class TrayStatus {idle, hold, manual};
extern TrayStatus trayStat;
void ctrlTray(void* param);

#endif