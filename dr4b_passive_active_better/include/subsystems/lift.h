#ifndef LIFT_H
#define LIFT_H

extern const int MAX_HEIGHT, MIN_HEIGHT;
extern const int onCubes[];

void runLeftLift(double percent);
void runRightLift(double percent);
void runLift(double percent);
void liftSafetyNet();
int getLiftHeight();
int getLiftSpeed();

enum class LiftStatus {idle, hold, slow, stack, uncontrolled};
extern LiftStatus liftStat;

extern int liftSetPoint;
extern bool resetIntegral;

void liftCtrl(void* param);
void setHold(bool updateSetPoint = true);
void updateLift();

void moveLiftUp(int setPoint, double mainPercent, double breakPercent = 0);
void moveLiftDown(int setPoint, double mainPercent, double breakPercent = 0);

/*extern int liftSetPoint;
extern bool holdLift, slowLift, stack;
extern bool resetPID;
extern int slowTimer;
void liftCtrl(void* param); //slows and holds lift on queues*/

#endif