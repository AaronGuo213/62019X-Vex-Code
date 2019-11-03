#include "main.h"

const int onCubes[] = {200, 500, 850, 1150, 1400, 1700, 2100, 2500};
const int onTower[] = {450, 1150, 800, 1400};

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

void liftToGnd(int threshhold) {

    liftStat = LiftStatus::manual;
    runLift(-100);
    while(getLiftHeight() > threshhold)
        delay(10);
    runLift(0);

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

int liftSetPoint;
bool resetIntegral = false;

void liftCtrl(void* param) {

    PID hold = initPID(1, 1, 0, 0.3, 0.0002, 0); //kP = 0.3, kI = 0.0001
    PID slow = initPID(0, 0, 1, 0, 0, 0.15); //kD = 0.15
    PID move = initPID(1, 1, 1, 0.45, 0.00012, 1.5);
    double holdVal = 0, slowVal = 0, moveVal = 0;
    int slowTimer = 300;

    while(true) {

        //std::cout << cubeSensor.get_value() << std::endl;
        slow.kD = cubeSensor.get_value() < 2000 ? 0.15 : 0.15;
        liftSetPoint = liftSetPoint > 2600 ? 2600 : liftSetPoint; //lift cannot be higher than 1800
        liftSetPoint = liftSetPoint < 0 ? 0 : liftSetPoint; //lift cannot be lower than 0

        if(resetIntegral) {
            hold.integral = 0;
            move.integral = 0;
            resetIntegral = false;
        }

        if(liftStat != LiftStatus::manual) {

            if(liftStat == LiftStatus::idle)
                runLift(0);

            else if(liftStat == LiftStatus::slow) {
        
                if(slowTimer == 0) { //once the lift has been slowed to prevent bouncing
                    slowTimer = 300;
                    setHold();
                    liftSetPoint = getLiftHeight(); //makes the lift hold at the current spot
                    std::cout << "switch" << std::endl;
                }
                else
                    slowTimer -= 10;

                slow.error = -getLiftHeight() * 5 / 7; //updates error for slowPID
                slowVal = runPID(&slow); //updates slowVal, refernce misc.cpp
                runLift(slowVal);

                //std::cout << "liftPos: " << getLiftHeight() << " | slow.derivative: " << slow.derivative << " | slowVal: " << slowVal << std::endl;

            }

            else if(liftStat == LiftStatus::hold) {

                hold.error = (liftSetPoint - getLiftHeight()) * 5 / 7; //updates error for holdPID
                holdVal = runPID(&hold); //updates the holdVal, reference misc.cpp
                runLift(holdVal);

                //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | hold.error: " << hold.error << " | holdVal: " << holdVal << std::endl;

            }

            else if(liftStat == LiftStatus::stack) {
                runLift(-100);
                if(getLiftHeight() < 30) {
                    liftSetPoint = 550;
                    setHold(0);
                }
            }

            else if(liftStat == LiftStatus::move) {

                move.error = (liftSetPoint - getLiftHeight()) * 5 / 7;
                moveVal = runPID(&move);
                runLift(moveVal);

                /*if(abs(move.error) < 10)
                    liftStat = LiftStatus::hold;*/
                //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | move.error: " << move.error << " | moveVal: " << moveVal << std::endl;

            }

        }

        else
            slowTimer = 300;

        liftSafetyNet();
        delay(10);

    }

}

void setHold(bool updateSetPoint) {

    liftStat = LiftStatus::hold;
    if(updateSetPoint)
        liftSetPoint = getLiftHeight();
    resetIntegral = true;

}

void updateLift() {

    if(l1() && !r1()) {
        liftStat = LiftStatus::manual;
        runLift(100);
    }

    else if(!l1() && r1()) {
        liftStat = LiftStatus::manual;
        runLift(-100);
    }

    else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN))
        liftStat = LiftStatus::idle;

    else if(liftStat == LiftStatus::manual || liftStat == LiftStatus::idle)
        liftStat = LiftStatus::slow;

}

void moveLift(int setPoint) {

    liftSetPoint = setPoint;
    resetIntegral = true;
    liftStat = LiftStatus::move;

}
