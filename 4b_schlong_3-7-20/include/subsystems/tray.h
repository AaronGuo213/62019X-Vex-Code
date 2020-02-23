#ifndef TRAY_H
#define TRAY_H

void runTray(double percent);
int getTrayPos();
double calcTrayPow(bool isOuttaking);
double calcTrayPowAuton(bool isOuttaking);
void updateTray();
void traySafetyNet();

extern double traySetPoint;
extern bool resetTrayIntegral;
enum class TrayStatus {idle, hold, manual};
extern TrayStatus trayStat;
void ctrlTray(void* param);
void setTrayHold(bool updateSetPoint = true);
void setTrayIdle();
void moveTray(int setPoint);

#endif