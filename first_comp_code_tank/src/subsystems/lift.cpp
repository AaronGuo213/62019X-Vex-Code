#include "main.h"

int potOffset = 0;

void runLeftLift(float percentage) {

    leftLift.move_voltage(percentage * 120);

}

void runRightLift(float percentage) {

    rightLift.move_voltage(percentage * 120);

}

int getLiftHeight() {

    return (liftPotLeft.get_value() - liftPotRight.get_value()) / 2 - potOffset;

}

bool manual = false, manualUsed = false, shiftUp = false, shiftDown = false, reset = false;
int height = 0, liftSetPoint;
int aboveCube[5] = {0, 0, 0, 0, 0};

void liftCtrl(void* param) {

    PID lift = initPID(0, 0, 0, 0, 0, 0);
    PID lean = initPID(0, 0, 0, 0, 0, 0);
    liftSetPoint = aboveCube[height];
    float liftVal, leanVal;

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

        if(leftLift.is_over_temp() || leftLift.is_over_current())
			leftLift.set_voltage_limit(0);
		else
			leftLift.set_voltage_limit(12000);

        if(rightLift.is_over_temp() || rightLift.is_over_current())
			rightLift.set_voltage_limit(0);
		else
			rightLift.set_voltage_limit(12000);

        lift.error = liftSetPoint - getLiftHeight();
        lean.error = liftPotLeft.get_value() + liftPotRight.get_value() - potOffset;
        liftVal = runPID(&lift);
        leanVal = runPID(&lean);
        runLeftLift(liftVal + leanVal);
        runRightLift(liftVal - leanVal);

        std::cout << liftSetPoint << " | " << getLiftHeight() << " | " << lift.error << "\n";

    }

    else if(manual) {

        liftSetPoint = getLiftHeight();

        if(leftLift.is_over_temp() || leftLift.is_over_current())
			leftLift.set_voltage_limit(0);
		else
			leftLift.set_voltage_limit(12000);

        if(rightLift.is_over_temp() || rightLift.is_over_current())
			rightLift.set_voltage_limit(0);
		else
			rightLift.set_voltage_limit(12000);

        shiftUp = false;
        shiftDown = false;
        manualUsed = true;

    }

    delay(1);

    }

}

void autoAllign() {

    int sonarDist = 0;
    float allignVal;
    PID allign = initPID(1, 0, 0, 0, 0, 0);

    if(manualUsed)
        shiftDown = true;

    if(height = 0)
        height = 1;

    while(abs(sonarDist - cubeSensor.get_value()) > 50) {

        allign.error = sonarDist - cubeSensor.get_value();
        allignVal = runPID(&allign);

        runLeftBase1(allignVal);
        runLeftBase2(allignVal);
        runRightBase1(allignVal);
        runRightBase2(allignVal);

        delay(1);
    
    }

    runLeftBase1(0);
    runLeftBase2(0);
    runRightBase1(0);
    runRightBase2(0);

}

void autoStack() {

    runClaw(-100, 150);
    height = 0;
    while(getLiftHeight !== 0)
        delay(1);
    runClaw(100, 150);

}