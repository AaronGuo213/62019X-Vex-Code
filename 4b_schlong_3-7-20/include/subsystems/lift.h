#ifndef LIFT_H
#define LIFT_H

extern const int atCube[];
extern const int onTower[];

void runLift(double percent);
void liftSafetyNet();
double getLiftHeight();

enum class LiftStatus {idle, hold, slow, move, manual};
extern LiftStatus liftStat;
extern int liftSetPoint;
extern double liftVel;
extern bool resetIntegral;

void ctrlLift(void* param);
void setLiftHold(bool updateSetPoint = true);
void setLiftIdle();

void moveLift(int setPoint);
struct liftQueue {
    int setPoint, queue;
};
void queueLift(void* param);
void moveLift(int setPoint, int queue);
void liftToGnd(double percentSpeed);
void updateLift();

#endif