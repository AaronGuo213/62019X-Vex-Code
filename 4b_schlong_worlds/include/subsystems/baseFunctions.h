#ifndef BASE_H
#define BASE_H

//drive straight functions
void moveDist(double distance, double maxVal = 100, int time = 0); //classic move straight
void moveDist(double distance, double switchDist, double maxVal1, double maxVal2, int time = 0); //2 different speed caps
void moveStraight(double distance, double percent); //moves at a constant velocity

//turn functions
void turnRelative(double angle, double maxVal = 100, int time = 0); //turns a relative angle using gyro
void turnAbsolute(double angle, double maxVal = 100, int time = 0); //turns to an absolute angle using gyro

//curve functions
void curveBase(double leftPow, double rightPow, double fastSideDist);
void curveBasePID(double leftSetPoint, double rightSetPoint, double maxVal = 100, int time = 0);

//other
double getDeployOffset(int time);
double getSonarInches(int numTimes, double dfault, double low, double high);

#endif