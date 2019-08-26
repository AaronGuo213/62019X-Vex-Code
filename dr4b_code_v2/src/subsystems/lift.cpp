#include "main.h"

int clawCount = 0, clawPercent;

void setIntk(bool status) {

    intk1.set_value(status);
    intk2.set_value(status);

}

void runLeftLift(float percent) {

    leftLift.move_voltage(percent * 120);

}

void runRightLift(float percent) {

    rightLift.move_voltage(percent * 120);

}

int getLiftHeight() {

    return liftPot.get_value() - 0;

}

int getLiftSpeed() {

    return (leftLift.get_actual_velocity() + rightLift.get_actual_velocity()) / 2;

}

int liftSetPoint;
bool holdLift = true, slowLift = false;

void liftCtrl(void* param) {

    PID hold = initPID(1, 0, 1, 0.2, 0, 2);
    PID slow = initPID(0, 1, 0, 0, 1, 0);
    float holdVal = 0, slowVal = 0;

    while(true) {

        if(holdLift) {

            liftSetPoint = liftSetPoint > 1910 ? 1910 : liftSetPoint;
            liftSetPoint = liftSetPoint < 0 ? 0 : liftSetPoint;
        
            hold.error = liftSetPoint - getLiftHeight();
            holdVal = runPID(&hold);

            runLeftLift(holdVal);
            runRightLift(holdVal);

            //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | hold.error: " << hold.error << " | holdVal: " << holdVal << std::endl;

            if(leftLift.is_over_temp() || leftLift.is_over_current())
                leftLift.set_voltage_limit(0);
            else
                leftLift.set_voltage_limit(12000);

            if(rightLift.is_over_temp() || rightLift.is_over_current())
                rightLift.set_voltage_limit(0);
            else
                rightLift.set_voltage_limit(12000);

            delay(10);

        }

        else if(slowLift) {

            if(getLiftSpeed() < 20) {
                holdLift = true;
                slowLift = false;
            }

            liftSetPoint = liftSetPoint > 1910 ? 1910 : liftSetPoint;
            liftSetPoint = liftSetPoint < 0 ? 0 : liftSetPoint;
        
            slow.error = liftSetPoint - getLiftHeight();
            slowVal = runPID(&slow);

            runLeftLift(slowVal);
            runRightLift(slowVal);

            //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | slow.error: " << slow.error << " | slowVal: " << slowVal << std::endl;
        
            if(leftLift.is_over_temp() || leftLift.is_over_current())
                leftLift.set_voltage_limit(0);
            else
                leftLift.set_voltage_limit(12000);

            if(rightLift.is_over_temp() || rightLift.is_over_current())
                rightLift.set_voltage_limit(0);
            else
                rightLift.set_voltage_limit(12000);

            delay(10);

        }

    }

}