#ifndef ODOMETRY_H
#define ODOMETERY_H

struct odometry {

    double L_SHIFT, R_SHIFT;
    double globalAngle;

    double currentL, currentR, prevL, prevR;
    double deltaL, deltaR, deltaAngle;

};

odometry initOdom(double currentAngle = 0);
void updateOdom(odometry *odom);

#endif