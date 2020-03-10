#include "main.h"

/*============
Odometry Class
============*/

const double LEFT_DISP = 2.26, RIGHT_DISP = 2.26;
double x, y, angle;
double angleChange, xChangeLocal, yChangeLocal, xChange, yChange;
double chordAngle;
double leftEncPrev = 0, rightEncPrev = 0;
double leftEncChange, rightEncChange;

//declaration function
Odometry::Odometry(double xStart, double yStart, double angleStart) {

    x = xStart;
    y = yStart;
    angle = angleStart * PI / 180;
    resetEnc();

}

//the almighty update function
void Odometry::update() {

    //updates data
    leftEncChange = getLeftEnc() - leftEncPrev;
    rightEncChange = getRightEnc() - rightEncPrev;
    leftEncPrev = getLeftEnc();
    rightEncPrev = getRightEnc();

    //calculates the change of angle
    angleChange = (rightEncChange - leftEncChange) / (LEFT_DISP + RIGHT_DISP);
    chordAngle = angle + (angleChange / 2);
    
    //calculates the position change in the local axes
    if(angleChange == 0) {
        //xChangeLocal = yawEncChange;
        yChangeLocal = rightEncChange;
    }

    else {
        //xChangeLocal = 2 * sin(angleChange / 2) * ((yawEncChange / angleChange) - YAW_DISP);
        yChangeLocal = 2 * sin(angleChange / 2) * ((rightEncChange / angleChange) + RIGHT_DISP);
    }
    
    //calculates the global position change
    xChange = yChangeLocal * cos(chordAngle);
    yChange = yChangeLocal * sin(chordAngle);
    /*xChange = xChangeLocal * sin(chordAngle) + yChangeLocal * cos(chordAngle);
    yChange = yChangeLocal * sin(chordAngle) - xChangeLocal * cos(chordAngle);*/
    
    //updates the absolute position and angle
    /*x += xChange; //true location calculation
    y += yChange;*/
    angle += angleChange;
    x += (leftEncChange + rightEncChange) / 2 * cos(angle); //trying a simpler location calculation
    y += (leftEncChange + rightEncChange) / 2 * sin(angle);

}

//get-value functions
double Odometry::getAngle() {
    return angle * 180 / PI;
}

double Odometry::getX() {
    return x;
}

double Odometry::getY() {
    return y;
}

/*==========
End of Class
==========*/

void trackPos(void* param) {

    std::uint32_t now = pros::millis();
    Odometry* odom = static_cast<Odometry*>(param);
    while(true) {

        odom->update();
        //std::cout << "x: " << odom.getX() << " | y: " << odom.getY() << " | angle: " << odom.getAngle() << std::endl;
        Task::delay_until(&now, 20);
    
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

void turnToPoint(Odometry* odom, double x, double y) {

    isSettled = false;
    PID turn = initPID(1, 0, 0, 2, 0, 0);
    double setPoint, turnVal;
    while(!isSettled) {

        setPoint = atan2((y - odom->getY()), (x - odom->getX())) * 180 / PI;
        turn.error = setPoint - odom->getAngle();
        turn.error = fixAngle(turn.error);
        if(turn.error < 3)
            isSettled = true;
        turnVal = runPID(&turn);

        runBase(-turnVal, turnVal);
        delay(10);

    }
    runBase(0, 0);

}

void turnToAngle(Odometry* odom, double angle) {

    isSettled = false;
    PID turn = initPID(1, 1, 1, 1.8, 0.00002, 9); //kP = 1.8, kI = 0.00002, kD = 9;
    double turnVal;
    while(!isSettled) {

        turn.error = angle - odom->getAngle();
        turn.error = fixAngle(turn.error);
        if(turn.error < 2)
            isSettled = true;
        turnVal = runPID(&turn);

        runBase(-turnVal, turnVal);
        delay(10);

    }
    runBase(0, 0);

}

void turnAngle(Odometry* odom, double angleChange) {

    isSettled = false;
    PID turn = initPID(1, 0, 0, 2, 0, 0);
    double setPoint = odom->getAngle() + angleChange;
    setPoint = fixAngle(setPoint);
    double turnVal;
    while(!isSettled) {

        turn.error = setPoint - odom->getAngle();
        turn.error = fixAngle(turn.error);
        if(turn.error < 3)
            isSettled = true;
        turnVal = runPID(&turn);

        runBase(-turnVal, turnVal);
        delay(10);

    }
    runBase(0, 0);

}


void moveToPointForwards(Odometry* odom, double x, double y) {

    isSettled = false;
    PID dist = initPID(1, 1, 1, 10, 0.004, 10);
    PID turn = initPID(1, 1, 1, 1.9, 0.00002, 9);
    double angleSetPoint, distBias;
    double turnVal, distVal;
    double leftVal, rightVal, maxVal;
    int count = 0;
    while(!isSettled) {

        angleSetPoint = atan2(y - odom->getY(), x - odom->getX()) * 180 / PI; //difference of current and goal angle
        turn.error = angleSetPoint - odom->getAngle();
        turn.error = fixAngle(turn.error);
        turnVal = runPID(&turn);

        distBias = abs(turn.error) > 90 ? 0 : cos(abs(turn.error * PI / 180));
        dist.error = sqrt(pow(y - odom->getY(), 2) + pow(x - odom->getX(), 2)); //distance formula
        distVal = runPID(&dist);
        distVal *= distBias;

        if(abs(dist.error) < 1)
            isSettled = true;
        else if(abs(dist.error) < 5)
            turnVal = 0;

        if(count % 50 == 0) {
            std::cout << "currentAngle: " << odom->getAngle() << " | targetAngle: " << angleSetPoint << " | angleError: " << turn.error << " | turnVal: " << turnVal << std::endl;
            std::cout << "position: (" << odom->getX() << ", " << odom->getY() << ") | goal: (" << x << ", " << y << ") | distError: " << dist.error << " | distVal: " << distVal << "\n\n";
        }
        count += 10;

        leftVal = distVal - turnVal;
        rightVal = distVal + turnVal;
        if(leftVal > 100 || rightVal > 100) {
            maxVal = leftVal > rightVal ? leftVal : rightVal;
            leftVal = leftVal / maxVal * 100;
            rightVal = rightVal / maxVal * 100;
        }
        runBase(distVal - turnVal, distVal + turnVal);
        delay(10);

    }
    runBase(0, 0);

}

void moveToPointBackwards(Odometry* odom, double x, double y) {

    isSettled = false;
    PID turn = initPID(1, 0, 0, 2, 0, 0);
    PID dist = initPID(1, 0, 0, 2, 0, 0);
    double angleSetPoint, distBias;
    double turnVal, distVal;
    while(!isSettled) {

        angleSetPoint = atan2(y - odom->getY(), x - odom->getX()) * 180 / PI; //difference of current and goal angle
        turn.error = angleSetPoint - odom->getAngle();
        turn.error = fixAngle(turn.error);
        turn.error = turn.error > 0 ? turn.error - 180 : turn.error + 180;
        turnVal = runPID(&turn);

        distBias = abs(turn.error) > 45 ? 0 : cos(abs(turn.error) * 2);
        dist.error = -sqrt(pow(y - odom->getY(), 2) + pow(x - odom->getX(), 2)); //distance formula
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

void moveToPoint(Odometry* odom, double x, double y) {

    double angleSetPoint = atan2(y - odom->getY(), x - odom->getX()) * 180 / PI;
    double angleDiff = angleSetPoint - odom->getAngle();
    angleDiff = fixAngle(angleDiff);
    if(abs(angleDiff) > 90)
        moveToPointBackwards(odom, x, y);
    else 
        moveToPointForwards(odom, x, y);

}