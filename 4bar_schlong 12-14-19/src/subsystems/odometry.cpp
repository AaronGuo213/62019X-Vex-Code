#include "main.h"

class Odometry {

    const int LEFT_DISP = 3.875, RIGHT_DISP = 3.875, YAW_DISP = 0;
    double x, y, angle;
    double angleChange, xChangeLocal, yChangeLocal, xChange, yChange;
    double chordAngle;
    double leftEncPrev, rightEncPrev, yawEncPrev;
    double leftEncChange, rightEncChange, yawEncChange;

    //private update functions
    void updateData() {

        leftEncChange = getLeftEnc() - leftEncPrev;
        rightEncChange = getRightEnc() - rightEncPrev;
        yawEncChange = getYawEnc() - yawEncPrev;
        leftEncPrev = getLeftEnc();
        rightEncPrev = getRightEnc();
        yawEncPrev = getYawEnc();

    }   

    void calcAngleChange() {

        angleChange = (rightEncChange - leftEncChange) / (LEFT_DISP + RIGHT_DISP);
        chordAngle = angle + (angleChange / 2);

    }

    void calcLocalChanges() {

        if(angleChange == 0) {
            xChange = yawEncChange;
            yChange = rightEncChange;
        }

        else {
            xChangeLocal = 2 * sin(angleChange / 2) * ((yawEncChange / angleChange) - YAW_DISP);
            yChangeLocal = 2 * sin(angleChange / 2) * ((rightEncChange / angleChange) - RIGHT_DISP);
        }

    }

    void calcGlobalChanges() {

        xChange = xChangeLocal * sin(chordAngle) + yChangeLocal * cos(chordAngle);
        yChange = yChangeLocal * sin(chordAngle) - xChangeLocal * cos(chordAngle);

    }

    void updateGlobalVars() {

        //x += xChange;
        //y += yChange;
        angle += angleChange;

    }


    public:

    //declaration function
    Odometry(double xStart, double yStart, double angleStart) {

        x = xStart;
        y = yStart;
        angle = angleStart;

    }

    //the almighty update function
    void update() {

        updateData();
        calcAngleChange();
        /*calcLocalChanges();
        calcGlobalChanges();*/
        updateGlobalVars();

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