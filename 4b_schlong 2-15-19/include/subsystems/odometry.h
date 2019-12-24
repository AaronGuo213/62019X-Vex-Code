#ifndef ODOMETRY_H
#define ODOMETERY_H

class Odometry;
void trackPos(void* param);

extern bool isSettled;
double fixAngle(double initAngle);

void turnToPoint(Odometry &odom, double x, double y);
void turnToAngle(Odometry &odom, double angle);
void turnAngle(Odometry &odom, double angleChange);

void moveToPointForwards(Odometry &odom, double x, double y);
void moveToPointBackwards(Odometry &odom, double x, double y);
void moveToPoint(Odometry &odom, double x, double y);

#endif