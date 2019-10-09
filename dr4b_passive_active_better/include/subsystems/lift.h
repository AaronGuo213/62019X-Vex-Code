#ifndef LIFT_H
#define LIFT_H

void runLeftLift(double percent);
void runRightLift(double percent);
void runLift(double percent);
void liftSafetyNet();
int getLiftHeight();
int getLiftSpeed();

enum class LiftStatus {idle, manual, hold, target, stack};
extern LiftStatus liftStat;
enum class TargetStatus {upSimple, downSimple};
extern TargetStatus targetStat;

extern int liftSetPoint, liftDelay;
extern double liftPercent;
extern bool resetIntegral;

void liftCtrl(void* param);
void setLift(double liftPercent, int delay = 10);
void setHold();
void updateLift();

void moveLiftUp(int setPoint, double mainPercent, double breakPercent = 0);
void moveLiftDown(int setPoint, double mainPercent, double breakPercent = 0);
void moveSimple();

/*extern int liftSetPoint;
extern bool holdLift, slowLift, stack;
extern bool resetPID;
extern int slowTimer;
void liftCtrl(void* param); //slows and holds lift on queues*/

#endif