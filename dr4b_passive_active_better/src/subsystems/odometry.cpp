#include "main.h"

odometry initOdom(double currentAngle) {

    double shift = (9 + 7/16) / 2;
    return {shift, shift, currentAngle, 0, 0, 0, 0, 0, 0, 0};

}

void updateOdom(odometry *odom) {

    odom->currentL = getLeftEnc() / 360 * 3.25 * M_PI;
    odom->currentR = getRightEnc() / 360 * 3.25 * M_PI;
    odom->deltaL = odom->currentL - odom->prevL;
    odom->deltaR = odom->currentR - odom->prevR;
    odom->deltaAngle = 180 / M_PI * (odom->deltaR - odom->deltaL) / (odom->R_SHIFT + odom->L_SHIFT);
    odom->globalAngle += odom->deltaAngle;
    odom->prevL = odom->currentL;
    odom->prevR = odom->currentR;

}