#include "main.h"

int clawCount = 0, //timer for the claw
    clawPercent; //determines what power the claw runs at

void runClaw(float percent, int time) { //function for running the claw

    clawCount = time; //assigns values to the global variables
    clawPercent = percent;

}

void clawCtrl(void* param) { //task for running the claw

    while(true) {

        if(clawCount > 0) { //while the timer is still running

            clawCount --; //remove 1ms from the timer
            claw1.move_voltage(clawPercent * 120);
            claw2.move_voltage(clawPercent * 120);

        }

        else {

            claw1.move_voltage(0);
            claw2.move_voltage(0);

        }

        delay(1);

    }

}

void runLeftLift(float percent) {

    leftLift.move_voltage(percent * 120);

}

void runRightLift(float percent) {

    rightLift.move_voltage(percent * 120);

}

int getLiftHeight() {

    return rightLiftPot.get_value() - 1030;

}

int liftSetPoint;
bool ctrlLift = true, slowHold = false;

void liftCtrl(void* param) {

    PID lift = initPID(1, 0, 1, 0.2, 0, 2);
    float liftVal = 0;

    while(true) {

        if(ctrlLift) {

            liftSetPoint = liftSetPoint > 1910 ? 1910 : liftSetPoint;
            liftSetPoint = liftSetPoint < 0 ? 0 : liftSetPoint;
        
            lift.error = liftSetPoint - getLiftHeight();
            liftVal = runPID(&lift);

            runLeftLift(liftVal);
            runRightLift(liftVal);

            //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | lift.error: " << lift.error << " | lean.error: " << lean.error << " | liftVal: " << liftVal << " | leanVal: " << leanVal << std::endl;
        
            if(leftLift.is_over_temp() || leftLift.is_over_current())
                leftLift.set_voltage_limit(0);
            else
                leftLift.set_voltage_limit(12000);
            if(rightLift.is_over_temp() || rightLift.is_over_current())
            rightLift.set_voltage_limit(0);
            else
                rightLift.set_voltage_limit(12000);

            delay(5);

        }

        else if(slowHold) {

            if(leftLift.get_actual_velocity() > 0) {
                runLeftLift(0);
                runRightLift(0);
                delay(5 * abs(leftLift.get_actual_velocity()));
            }
            else {
                leftLift.move_velocity(0);
                rightLift.move_velocity(0);
                delay(5 * abs(leftLift.get_actual_velocity()));
            }
            liftSetPoint = getLiftHeight();
            slowHold = false;
            ctrlLift = true;

        }

    }

}