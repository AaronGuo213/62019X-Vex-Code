#ifndef BASE_H
#define BASE_H

//drive straight functions
void moveStraight(double distance, double maxVal = 100);
void moveStraight(double distance, bool stopEarly, int time, double maxVal = 100);
void moveStraight(double distance, double switchDist, bool stopEarly, int time, double maxVal1, double maxVal2);
void moveStraightCut(double distance, double setPoint, double maxVal = 100);

//turn functions
void turn(double angle, double maxVal = 100);
void turn(double angle, bool stopEarly, int time, double maxVal = 100);
void turnRelative(double angle, double maxVal = 100);
void turnAbsolute(double angle, double maxVal = 100);
void turnToCorner(double initVal = 100);

//curve functions
void curveBase(double leftPow, double rightPow, double fastSideDist);
void curveBasePID(double leftSetPoint, double rightSetPoint, double maxVal = 100);
void curveBasePID(double leftSetPoint, double rightSetPoint, int time, double maxVal);
void curveBasePIDCut(double leftSetPoint, double rightSetPoint, double fastSideDist, double maxVal = 100);
void curveBaseCombo(double dist, double angle, int time, double maxVal = 100);

//other
double getDeployOffset(int time);

#endif