#ifndef LIFT_H
#define LIFT_H

extern const int MAX_HEIGHT, MIN_HEIGHT;
extern const int onCubes[];
extern const int onTower[];

void runLeftLift(double percent);
void runRightLift(double percent);
void runLift(double percent);
void liftSafetyNet();
int getLiftHeight();
int getLiftSpeed();

enum class LiftStatus {idle, hold, slow, stack, move, uncontrolled};
extern LiftStatus liftStat;

extern int liftSetPoint;
extern bool resetIntegral;

void liftCtrl(void* param);
void setHold(bool updateSetPoint = true);
void updateLift();
void moveLift(int setPoint);

#endif