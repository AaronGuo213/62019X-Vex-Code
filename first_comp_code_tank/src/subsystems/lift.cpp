#include "main.h"

void runLift(float percentage) {

    lift1.move_voltage(percentage * 120);
    lift2.move_voltage(percentage * 120);

}

bool manual = false, manualUsed = false, shiftUp = false, shiftDown = false, reset = false;
int height = 0, liftSetPoint;
int aboveCube[5] = {1110, 1560, 1910, 2320, 2930};

void liftCtrl(void* param) {

    PID lift = initPID(1, 1, 0, 0.2, 0.0001, 0);
    liftSetPoint = aboveCube[height];
    int liftVal;

    while(true) {

    if(!manual) {
        
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

            if(shiftDown) {

                for(int i = 0; i < 5; i++) {

                    if(liftSetPoint < aboveCube[i])
                        height = i;
                    break;

                }

                liftSetPoint = aboveCube[height];
                manualUsed = false;

            }

            else if(shiftUp) {

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
        runLift(-liftVal);

        std::cout << liftSetPoint << " | " << liftPot.get_value() << " | " << lift.error << "\n";

    }

    else if(manual) {

        liftSetPoint = liftPot.get_value();

        if(lift2.is_over_temp() || lift2.is_over_current())
			lift2.set_voltage_limit(0);
		else
			lift2.set_voltage_limit(12000);

        shiftUp = false;
        shiftDown = false;
        manualUsed = true;

    }

    delay(1);

    }

}

void autostack() {

    int sonarDist = 0, cubeDisp;
    float allignVal;
    PID allign = initPID(1, 0, 0, 0, 0, 0);

    if(manualUsed)
        shiftDown = true;

    if(height = 0)
        height = 1;

    cubeDisp = height;

    while(abs(sonarDist - cubeSensor.get_value()) > 50) {

        allign.error = sonarDist - cubeSensor.get_value();
        allignVal = runPID(&allign);

        runLeftBase(allignVal);
        runRightBase(allignVal);

        delay(1);
    
    }

    runLeftBase(0);
    runRightBase(0);

    runClaw(-100, 150);
    height = 0;

    for(int i = 0; i < (cubeDisp * 500); i++) {

        allign.error = sonarDist - cubeSensor.get_value();
        allignVal = runPID(&allign);

        runLeftBase(allignVal);
        runRightBase(allignVal);

        delay(1);

    }

    runClaw(100, 150);

}