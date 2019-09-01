#include "main.h"

void setIntk(bool status) {

    intk1.set_value(status);
    intk2.set_value(status);

}

void runLeftLift(float percent) {

    leftLift.move_voltage(percent * 120); //runs the leftLift motor out of 12000mV

}

void runRightLift(float percent) {

    rightLift.move_voltage(percent * 120); //runs the rightLift motor out of 12000mV

}

int getLiftHeight() {

    return liftPot.get_value();

}

int getLiftSpeed() {

    return (leftLift.get_actual_velocity() + rightLift.get_actual_velocity()) / 2;

}

int liftSetPoint; //setPoint that lift PID moves to and holds at
bool holdLift = true, slowLift = false;

void liftCtrl(void* param) {

    PID hold = initPID(1, 0, 1, 0.4, 0, 2); //kP = 0.4, kD = 2
    PID slow = initPID(0, 0, 1, 0, 0, 0.1); //kD = 0.1
    float holdVal = 0, slowVal = 0;

    while(true) {

        if(holdLift) {

            liftSetPoint = liftSetPoint > 2150 ? 2150 : liftSetPoint; //lift cannot be higher than 2150
            liftSetPoint = liftSetPoint < 275 ? 275 : liftSetPoint; //lift cannot be lower than 275
        
            hold.error = liftSetPoint - getLiftHeight(); //updates error for holdPID
            holdVal = runPID(&hold); //updates the holdVal, referecne misc.cpp

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

        }

        else if(slowLift) {

            if(abs(getLiftSpeed()) < 2) { //once the lift has been slowed to prevent bouncing,
                liftSetPoint = liftPot.get_value(); //makes the lift hold at the current spot
                holdLift = true; //switches to hold lift
                slowLift = false;
                slow.error = 0.0; //resets slowError
            }

            liftSetPoint = liftSetPoint > 2150 ? 2150 : liftSetPoint; //lift cannot be higher than 2150
            liftSetPoint = liftSetPoint < 275 ? 275 : liftSetPoint; //lift cannot be lower than 275
        
            slow.error = liftSetPoint - getLiftHeight(); //updates error for slowPID
            slowVal = runPID(&slow); //updates slowVal, refernce misc.cpp

            runLeftLift(slowVal);
            runRightLift(slowVal);

            std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | slow.error: " << slow.error << " | slowVal: " << slowVal << std::endl;
        
            if(leftLift.is_over_temp() || leftLift.is_over_current())
                leftLift.set_voltage_limit(0);
            else
                leftLift.set_voltage_limit(12000);

            if(rightLift.is_over_temp() || rightLift.is_over_current())
                rightLift.set_voltage_limit(0);
            else
                rightLift.set_voltage_limit(12000);

        }

        delay(10);
    }

}