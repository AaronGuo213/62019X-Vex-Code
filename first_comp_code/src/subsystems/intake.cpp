#include "main.h"

void runLift(float percentage) {

    lift1.move_voltage(percentage * 120);
    lift2.move_voltage(percentage * 120);

}

void runClaw(float percentage) {

    claw1.move_voltage(percentage * 120);
    claw2.move_voltage(percentage * 120);

}

bool manual = false, manualUsed = false, shiftUp = false, shiftDown = false, reset = false;
int height = 0, liftSetPoint;
int aboveCube[5] = {0, 10, 20, 30, 40};

void liftCtrl(void* param) {

    PID lift = initPID(0, 0, 0, 0, 0, 0);
    liftSetPoint = aboveCube[height];
    int liftVal;

    while(!manual) {
        
        if(reset) {
            reset = false;
            height = 0;
            liftSetPoint = aboveCube[height];
        }

        if(!manualUsed) {

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

        else if(manualUsed) {

            if(shiftUp) {

                for(int i = 0; i < 5; i++) {

                    if(liftSetPoint < aboveCube[i])
                        height = i;
                    break;

                }

                liftSetPoint = aboveCube[height];
                manualUsed = false;

            }

            else if(shiftDown) {

                for(int i = 4; i >= 0; i--) {

                    if(liftSetPoint > aboveCube[i])
                        height = i;
                    break;

                }

                liftSetPoint = aboveCube[height];
                manualUsed = false;

            }

        }

        if(lift2.is_over_temp() || lift2.is_over_current())
			lift2.set_voltage_limit(0);
		else
			lift2.set_voltage_limit(12000);

        lift.error = liftSetPoint - liftPot.get_value();
        liftVal = runPID(&lift);
        runLift(liftVal);

        delay(1);

    }

    if(manual) {

        liftSetPoint = liftPot.get_value();

        if(lift2.is_over_temp() || lift2.is_over_current())
			lift2.set_voltage_limit(0);
		else
			lift2.set_voltage_limit(12000);

        shiftUp = false;
        shiftDown = false;
        manualUsed = true;

    }

}

void autostack(int cubes) {

    if(!manualUsed) {

        int heightF = height - cubes;

        while(!cubeSensor.get_value() == 0) {
            runLeftBase1((0 - cubeSensor.get_value()) * 0);
            runLeftBase2((0 - cubeSensor.get_value()) * 0);
            runRightBase1((0 - cubeSensor.get_value()) * 0);
            runRightBase2((0 - cubeSensor.get_value()) * 0);
        }

        runClaw(-100);
        delay(300);
        liftSetPoint = aboveCube[heightF >= 0 ? heightF : 0];

        while(abs(liftPot.get_value() - liftSetPoint) > 10) {
            if(!cubeSensor.get_value() == 0) {
                runLeftBase1((0 - cubeSensor.get_value()) * 0);
                runLeftBase2((0 - cubeSensor.get_value()) * 0);
                runRightBase1((0 - cubeSensor.get_value()) * 0);
                runRightBase2((0 - cubeSensor.get_value()) * 0);
            }
        }

        runClaw(100);
        delay(300);

    }

}