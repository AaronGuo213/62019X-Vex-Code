#include "main.h"

const int MAX_HEIGHT = 200, MIN_HEIGHT = 1600;
const int onCubes[] = {50, 300, 600, 900, 1200, 1500, 1800, 2100};

void runLeftLift(double percent) {

    leftLift.move_voltage(percent * 120); //runs the leftLift motor out of 12000mV

}

void runRightLift(double percent) {

    rightLift.move_voltage(percent * 120); //runs the rightLift motor out of 12000mV

}

void runLift(double percent) {

    leftLift.move_voltage(percent * 120); //runs lift motors out of 12000mV
    rightLift.move_voltage(percent * 120);

}

void liftSafetyNet() { //prevents the motors from overheating and breaking

    if(leftLift.is_over_temp())
        leftLift.set_voltage_limit(0);
    else
        leftLift.set_voltage_limit(12000);

    if(rightLift.is_over_temp())
        rightLift.set_voltage_limit(0);
    else
        rightLift.set_voltage_limit(12000);

}

int getLiftHeight() {

    return liftPot.get_value() - 900;

}

int getLiftSpeed() {

    return (leftLift.get_actual_velocity() + rightLift.get_actual_velocity()) / 2;

}

enum class LiftStatus;
LiftStatus liftStat = LiftStatus::idle;

int liftSetPoint, liftDelay;
double liftPercent;
bool resetIntegral = false;

void liftCtrl(void* param) {

    PID holdLift = initPID(1, 1, 0, 0.3, 0.0002, 0); //kP = 0.3, kI = 0.0001
    double holdVal = 0;

    while(true) {

        if(liftStat == LiftStatus::uncontrolled) {

            if(liftStat == LiftStatus::idle)
                runLift(0);

            else if(liftStat == LiftStatus::manual) {
                runLift(liftPercent);
                delay(liftDelay);
            }

            else if(liftStat == LiftStatus::hold) {

                if(resetIntegral) {
                    holdLift.integral = 0;
                    resetIntegral = false;
                }

                liftSetPoint = liftSetPoint > 1800 ? 1800 : liftSetPoint; //lift cannot be higher than 1800
                liftSetPoint = liftSetPoint < 0 ? 0 : liftSetPoint; //lift cannot be lower than 0
    
                holdLift.error = liftSetPoint - getLiftHeight(); //updates error for holdPID
                holdVal = runPID(&holdLift); //updates the holdVal, reference misc.cpp

                runLift(holdVal);

                std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | hold.error: " << holdLift.error << " | holdVal: " << holdVal << std::endl;

                delay(10);

            }

            else if(liftStat == LiftStatus::stack) {
                runLift(-100);
                if(liftSwitch.get_value()) {
                    liftSetPoint = 600;
                    setHold();
                }
            }

        }

        liftSafetyNet();

    }

}

void setLift(double percent, int delay) {

    liftPercent = percent;
    liftDelay = delay;

}

void setHold() {

    liftStat = LiftStatus::hold;
    resetIntegral = true;

}

void updateLift() {

    if(r1() && !l1()) {
        liftStat = LiftStatus::manual;
        setLift(getLiftHeight() > MAX_HEIGHT ? 50 : 100);
        liftSetPoint = getLiftHeight();
    }

    else if(!r1() && l1()) {
        liftStat = LiftStatus::manual;
        setLift(getLiftHeight() < MIN_HEIGHT ? -20 : -100);
        liftSetPoint = getLiftHeight();
    }

    else
        setHold();

}

void moveLiftUp(int setPoint, double mainPercent, double brakePercent) { //use absolute value of percents

    liftStat = LiftStatus::uncontrolled;
    runLift(mainPercent);

    while(setPoint > getLiftHeight())
        delay(10);
    if(brakePercent){
        runLift(brakePercent);
        delay(300);
    }
    setHold();

}

void moveLiftDown(int setPoint, double mainPercent, double brakePercent) { //use absolute value of percents

    liftStat = LiftStatus::uncontrolled;
    runLift(-mainPercent);

    while(setPoint < getLiftHeight())
        delay(10);
    if(brakePercent){
        runLift(-brakePercent);
        delay(300);
    }
    setHold();

}









/*int liftSetPoint; //setPoint that lift PID moves to and holds at
bool holdLift = true, slowLift = false, stack = false;
bool resetPID = false;
int slowTimer = 300;

void liftCtrl(void* param) {

    PID hold = initPID(1, 1, 0, 0.3, 0.0002, 0); //kP = 0.3, kI = 0.0001
    PID slow = initPID(0, 0, 1, 0, 0, 0.15); //kD = 0.15
    double holdVal = 0, slowVal = 0;

    while(true) {

        if(resetPID) {
            resetPID = false;
            hold.error = 0;
            hold.prevError = 0;
            hold.integral = 0;
        }

        if(stack) {

            if(getLiftHeight() > 450)
                liftSetPoint = 300;

            else {
                stack = false;
                liftSetPoint = 700;
            }

        }

        if(holdLift) {

            liftSetPoint = liftSetPoint > 2150 ? 2150 : liftSetPoint; //lift cannot be higher than 2150
            liftSetPoint = liftSetPoint < 300 ? 300 : liftSetPoint; //lift cannot be lower than 275
        
            hold.error = liftSetPoint - getLiftHeight(); //updates error for holdPID
            holdVal = runPID(&hold); //updates the holdVal, referecne misc.cpp

            runLeftLift(holdVal);
            runRightLift(holdVal);

            std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | hold.error: " << hold.error << " | holdVal: " << holdVal << std::endl;

        }

        else if(slowLift) {

            liftSetPoint = liftSetPoint > 2150 ? 2150 : liftSetPoint; //lift cannot be higher than 2150
            liftSetPoint = liftSetPoint < 300 ? 300 : liftSetPoint; //lift cannot be lower than 275
        
            slow.error = liftSetPoint - getLiftHeight(); //updates error for slowPID
            
            //std::cout << "error: " << slow.error << " | prevError: " << slow.prevError << " | speed: " << getLiftSpeed() << std::endl;
            if(slowTimer <= 0) { //once the lift has been slowed to prevent bouncing
                holdLift = true; //switches to hold lift
                slowLift = false;
                liftSetPoint = liftPot.get_value(); //makes the lift hold at the current spot
                std::cout << "switch" << std::endl;
            }

            else
                slowTimer -= 10;

            slowVal = runPID(&slow); //updates slowVal, refernce misc.cpp

            runLeftLift(slowVal);
            runRightLift(slowVal);

            std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | slow.error: " << slow.error << " | slowVal: " << slowVal << " | speed: " << getLiftSpeed() << std::endl;

        }

        //prevents the motors from overheating and breaking
        if(leftLift.is_over_temp())
            leftLift.set_voltage_limit(0);
        else
            leftLift.set_voltage_limit(12000);

        if(rightLift.is_over_temp())
            rightLift.set_voltage_limit(0);
        else
            rightLift.set_voltage_limit(12000);

        delay(10);
        
    }

}*/