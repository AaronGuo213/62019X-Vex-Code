#ifndef BASE_H
#define BASE_H

//drive straight functions
void moveStraight(double distance, double maxVal = 100); //stops when base stops moving
void moveStraight(double distance, bool stopEarly, int time, double maxVal = 100); //stops with time
void moveStraight(double distance, double switchDist, bool stopEarly, int time, double maxVal1, double maxVal2); //stops with time
void moveStraightCut(double distance, double setPoint, double maxVal = 100); //stops with time

//turn functions
void turn(double angle, double maxVal = 100); //stops when base stops moving
void turn(double angle, bool stopEarly, int time, double maxVal = 100); //stops with time
void turnRelative(double angle, double maxVal = 100); //stops when base stops moving, uses gyro
void turnAbsolute(double angle, double maxVal = 100); //stops when base stops moving, uses gyro

//curve functions
void curveBase(double leftPow, double rightPow, double fastSideDist);
void curveBasePID(double leftSetPoint, double rightSetPoint, double maxVal = 100);
void curveBasePID(double leftSetPoint, double rightSetPoint, int time, double maxVal);
void curveBasePIDCut(double leftSetPoint, double rightSetPoint, double fastSideDist, double maxVal = 100);
void curveBaseCombo(double dist, double angle, int time, double maxVal = 100);

//other
double getDeployOffset(int time);

#endif