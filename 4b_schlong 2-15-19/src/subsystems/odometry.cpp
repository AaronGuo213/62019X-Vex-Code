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
            xChangeLocal = yawEncChange;
            yChangeLocal = rightEncChange;
        }

        else {
            xChangeLocal = 2 * sin(angleChange / 2) * ((yawEncChange / angleChange) - YAW_DISP);
            yChangeLocal = 2 * sin(angleChange / 2) * ((rightEncChange / angleChange) - RIGHT_DISP);
        }*/
        
        //calculates the global position change
        /*xChange = xChangeLocal * sin(chordAngle) + yChangeLocal * cos(chordAngle);
        yChange = yChangeLocal * sin(chordAngle) - xChangeLocal * cos(chordAngle);*/

        //5225 method
        /*xChange = yChangeLocal * sin(chordAngle) + xChangeLocal * cos(chordAngle);
        yChange = yChangeLocal * cos(chordAngle) - xChangeLocal * sin(chordAngle);*/
        
        //updates the absolute position and angle
        //x += xChange;
        //y += yChange;
        angle += angleChange;

    }

    //get value functions
    double getAngle() {
        return angle * 180 / PI;
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


bool isSettled = true;

double fixAngle(double initAngle) {

    while(initAngle > 180)
        initAngle -= 360;
    while(initAngle <= -180)
        initAngle += 360;
    return initAngle;

}

void turnToPoint(Odometry &odom, double x, double y) {

    isSettled = false;
    PID turn = initPID(1, 0, 0, 2, 0, 0);
    double setPoint, turnVal;
    while(!isSettled) {

        setPoint = atan2((y - odom.getY()), (x - odom.getX())) * 180 / PI;
        turn.error = setPoint - odom.getAngle();
        turn.error = fixAngle(turn.error);
        if(turn.error < 3)
            isSettled = true;
        turnVal = runPID(&turn);

        runBase(-turnVal, turnVal);
        delay(10);

    }
    runBase(0, 0);

}

void turnToAngle(Odometry &odom, double angle) {

    isSettled = false;
    PID turn = initPID(1, 0, 0, 2, 0, 0);
    double turnVal;
    while(!isSettled) {

        turn.error = angle - odom.getAngle();
        turn.error = fixAngle(turn.error);
        if(turn.error < 3)
            isSettled = true;
        turnVal = runPID(&turn);

        runBase(-turnVal, turnVal);
        delay(10);

    }
    runBase(0, 0);

}

void turnAngle(Odometry &odom, double angleChange) {

    isSettled = false;
    PID turn = initPID(1, 0, 0, 2, 0, 0);
    double setPoint = odom.getAngle() + angleChange;
    setPoint = fixAngle(setPoint);
    double turnVal;
    while(!isSettled) {

        turn.error = setPoint - odom.getAngle();
        turn.error = fixAngle(turn.error);
        if(turn.error < 3)
            isSettled = true;
        turnVal = runPID(&turn);

        runBase(-turnVal, turnVal);
        delay(10);

    }
    runBase(0, 0);

}


void moveToPointForwards(Odometry &odom, double x, double y) {

    isSettled = false;
    PID turn = initPID(1, 0, 0, 2, 0, 0);
    PID dist = initPID(1, 0, 0, 2, 0, 0);
    double angleSetPoint, distBias;
    double turnVal, distVal;
    while(!isSettled) {

        angleSetPoint = atan2(y - odom.getY(), x - odom.getX()) * 180 / PI; //difference of current and goal angle
        turn.error = angleSetPoint - odom.getAngle();
        turn.error = fixAngle(turn.error);
        turnVal = runPID(&turn);

        distBias = abs(turn.error) > 45 ? 0 : cos(abs(turn.error) * 2);
        dist.error = sqrt(pow(y - odom.getY(), 2) + pow(x - odom.getX(), 2)); //distance formula
        distVal = runPID(&dist);
        distVal *= distBias;

        if(abs(dist.error) < 2)
            isSettled = true;
        else if(abs(dist.error) < 5)
            turnVal = 0;

        runBase(distVal - turnVal, distVal + turnVal);
        delay(10);

    }
    runBase(0, 0);

}

void moveToPointBackwards(Odometry &odom, double x, double y) {

    isSettled = false;
    PID turn = initPID(1, 0, 0, 2, 0, 0);
    PID dist = initPID(1, 0, 0, 2, 0, 0);
    double angleSetPoint, distBias;
    double turnVal, distVal;
    while(!isSettled) {

        angleSetPoint = atan2(y - odom.getY(), x - odom.getX()) * 180 / PI; //difference of current and goal angle
        turn.error = angleSetPoint - odom.getAngle();
        turn.error = fixAngle(turn.error);
        turn.error = turn.error > 0 ? turn.error - 180 : turn.error + 180;
        turnVal = runPID(&turn);

        distBias = abs(turn.error) > 45 ? 0 : cos(abs(turn.error) * 2);
        dist.error = -sqrt(pow(y - odom.getY(), 2) + pow(x - odom.getX(), 2)); //distance formula
        distVal = runPID(&dist);
        distVal *= distBias;

        if(abs(dist.error) < 2)
            isSettled = true;
        else if(abs(dist.error) < 5)
            turnVal = 0;

        runBase(distVal - turnVal, distVal + turnVal);
        delay(10);

    }
    runBase(0, 0);

}

void moveToPoint(Odometry &odom, double x, double y) {

    double angleSetPoint = atan2(y - odom.getY(), x - odom.getX()) * 180 / PI;
    double angleDiff = angleSetPoint - odom.getAngle();
    angleDiff = fixAngle(angleDiff);
    if(abs(angleDiff) > 90)
        moveToPointBackwards(odom, x, y);
    else 
        moveToPointForwards(odom, x, y);

}