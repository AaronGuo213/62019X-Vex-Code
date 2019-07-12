#include "main.h"

void runClaw1(float percentage) {

    claw1.move_voltage(percentage * 120);

}

void runClaw2(float percentage) {

    claw2.move_voltage(percentage * 120);

}

int potOffset = 0;

void runLeftLift(float percentage) {

    leftLift.move_voltage(percentage * 120);

}

void runRightLift(float percentage) {

    rightLift.move_voltage(percentage * 120);

}

int getLiftHeight() {

    return (liftPotLeft.get_value() - liftPotRight.get_value() - potOffset) / 2;

}

/*bool manual = false, manualUsed = false, shiftUp = false, shiftDown = false, reset = false;
int height = 0, liftSetPoint;
int aboveCube[5] = {0, 0, 0, 0, 0};

void liftCtrl(void* param) {

    PID lift = initPID(0, 0, 0, 0, 0, 0);
    PID lean = initPID(0, 0, 0, 0, 0, 0);
    liftSetPoint = aboveCube[height];
    float liftVal, leanVal;

    while(true) {

        if(!manual) {

            if(shiftUp) {
                shiftUp = false;
                if(height < 4)
                    height++;
                liftSetPoint = aboveCube[height];
            }

            else if(shiftDown) {
                shiftDown = false;
                if(height > 0)
                    height--;
                liftSetPoint = aboveCube[height];
            }

        }

        else if(manual) {

            if(shiftDown) {

                for(int i = 0; i < 5; i++) {

                    if(liftSetPoint < aboveCube[i])
                        height = i;
                    break;

                }

                liftSetPoint = aboveCube[height];
                manual = false;

            }

            else if(shiftUp) {

                for(int i = 4; i >= 0; i--) {

                    if(liftSetPoint > aboveCube[i])
                        height = i;
                    break;

                }

                liftSetPoint = aboveCube[height];
                manual = false;

            }

        }

    }

}

void autoAllign() {

    int sonarDist = 0;
    float allignVal;
    PID allign = initPID(1, 0, 0, 0, 0, 0);

    if(manual)
        shiftDown = true;

    if(height == 0)
        height = 1;

    while(abs(sonarDist - cubeSensor.get_value()) > 50) {

        allign.error = sonarDist - cubeSensor.get_value();
        allignVal = runPID(&allign);

        runLeftBase(allignVal);
        runRightBase(allignVal);

        delay(1);
    
    }

    runLeftBase(0);
    runRightBase(0);

}

void autoStack() {

    claw.set_value(0);
    height = 0;
    while(!getLiftHeight == 0)
        delay(1);
    claw.set_value(1);

}*/