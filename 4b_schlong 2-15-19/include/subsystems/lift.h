#ifndef LIFT_H
#define LIFT_H

extern const int atCube[];
extern const int onTower[];

void runLift(double percent);
void liftSafetyNet();
double getLiftHeight();
int getLiftPot();

enum class LiftStatus {idle, hold, slow, move, manual, holdDown};
extern LiftStatus liftStat;
extern int liftSetPoint;
extern bool resetIntegral;

void ctrlLift(void* param);
void setLiftHold(bool updateSetPoint = true);
void setLiftIdle();
void moveLift(int setPoint);
void updateLift();

#endif