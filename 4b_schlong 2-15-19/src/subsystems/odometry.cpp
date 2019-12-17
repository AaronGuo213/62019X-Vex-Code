#include "main.h"

class Odometry {

    const int LEFT_DISP = 3.875, RIGHT_DISP = 3.875, YAW_DISP = 0;
    double x, y, angle;
    double angleChange, xChangeLocal, yChangeLocal, xChange, yChange;
    double chordAngle;
    double leftEncPrev, rightEncPrev, yawEncPrev;
    double leftEncChange, rightEncChange, yawEncChange;

    public:

    //declaration function
    Odometry(double xStart, double yStart, double angleStart) {

        x = xStart;
        y = yStart;
        angle = angleStart;

    }

    //the almighty update function
    void update() {

        //updates data
        leftEncChange = getLeftEnc() - leftEncPrev;
        rightEncChange = getRightEnc() - rightEncPrev;
        yawEncChange = getYawEnc() - yawEncPrev;
        leftEncPrev = getLeftEnc();
        rightEncPrev = getRightEnc();
        yawEncPrev = getYawEnc();

        //calculates the change of angle
        angleChange = (rightEncChange - leftEncChange) / (LEFT_DISP + RIGHT_DISP);
        chordAngle = angle + (angleChange / 2);
        
        //calculates the position change in the local axes
        /*if(angleChange == 0) {
            xChange = yawEncChange;
            yChange = rightEncChange;
        }

        else {
            xChangeLocal = 2 * sin(angleChange / 2) * ((yawEncChange / angleChange) - YAW_DISP);
            yChangeLocal = 2 * sin(angleChange / 2) * ((rightEncChange / angleChange) - RIGHT_DISP);
        }*/
        
        //calculates the global position change
        /*xChange = xChangeLocal * sin(chordAngle) + yChangeLocal * cos(chordAngle);
        yChange = yChangeLocal * sin(chordAngle) - xChangeLocal * cos(chordAngle);*/
        
        //updates the absolute position and angle
        //x += xChange;
        //y += yChange;
        angle += angleChange;

    }

    //get value functions
    double getAngle() {
        return angle;
    }
    
    double getX() {
        return x;
    }

    double getY() {
        return y;
    }

};

void trackPos(void* param) {

    std::uint32_t now = pros::millis();
    Odometry tracker = Odometry(0, 0, 0);
    while(true) {

        tracker.update();
        //std::cout << tracker.getAngle() * 180 / M_PI << std::endl;
        Task::delay_until(&now, 50);
    
    }

}