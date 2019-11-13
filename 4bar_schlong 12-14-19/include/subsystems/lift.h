#ifndef LIFT_H
#define LIFT_H

extern const int onCubes[];
extern const int onTower[];

void runLift(double percent);
void liftToGnd(int threshhold);
void liftSafetyNet();
int getLiftHeight();

enum class LiftStatus {idle, hold, slow, move, manual};
extern LiftStatus liftStat;
extern int liftSetPoint;
extern bool resetIntegral;

void liftCtrl(void* param);
void setHold(bool updateSetPoint = true);
void updateLift();
void moveLift(int setPoint);

#endif