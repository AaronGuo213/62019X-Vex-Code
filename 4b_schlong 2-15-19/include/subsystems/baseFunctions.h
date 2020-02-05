#ifndef BASE_H
#define BASE_H

void moveStraight(double distance, bool stopEarly, int time, double maxVal = 100);
void moveStraight(double distance, double switchDist, bool stopEarly, int time, double maxVal1, double maxVal2);
void moveStraightCut(double distance, double setPoint, double maxVal = 100);
void turn(double angle, bool stopEarly, int time, double maxVal = 100);
void curveBase(double leftPow, double rightPow, double fastSideDist);
void curveBasePID(double leftSetPoint, double rightSetPoint, int time, double maxVal = 100);
void curveBaseCombo(double dist, double angle, int time, double maxVal = 100);
void curveBaseVel(double leftSetPoint, double rightSetPoint, int time, double maxVal = 100);
void curveBaseVelCut(double leftSetPoint, double rightSetPoint, double fastSideDist, double maxVal = 100);

#endif