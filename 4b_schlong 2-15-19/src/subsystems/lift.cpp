#include "main.h"

const int atCube[] = {0, 0, 250, 460, 600, 850}; //array for cube heights
const int onTower[] = {800, 800, 950}; //array for tower heights

void runLift(double percent) {

    lift.move_voltage(percent * 120); //runs the lift motor out of 12000mV

}

void liftSafetyNet() { 
    
    //prevents the motors from overheating and breaking
    if(lift.is_over_temp())
        lift.set_voltage_limit(0);
    else
        lift.set_voltage_limit(12000);

}

double getLiftHeight() {

    return lift.get_position();

}

enum class LiftStatus; //states for the current lift status
LiftStatus liftStat = LiftStatus::idle;

int liftSetPoint; //determines where the lift actively tries to move to
bool resetIntegral = false; //determines when to reset the integral buildup

void ctrlLift(void* param) {

    std::uint32_t now = millis();
    PID hold = initPID(1, 1, 0, 1.2, 0.0008, 0); //kP = 1.2, kI = 0.0008
    PID slow = initPID(0, 0, 1, 0, 0, 0.6); //kD = 0.6
    PID move = initPID(1, 1, 1, 1.8, 0.00048, 6); //kP = 1.8, kI = 0.00048, kD = 6
    double holdVal = 0, slowVal = 0, moveVal = 0;
    int slowTimer = 300;

    while(true) {

        //std::cout << cubeSensor.get_value() << std::endl;
        liftSetPoint = liftSetPoint > 950 ? 950 : liftSetPoint; //lift cannot be higher than 750
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
                    slowTimer = 300; //reset the slow timer
                    setLiftHold(); //switch to hold mode
                }
                else
                    slowTimer -= 10;

                slow.error = -getLiftHeight(); //updates error for slowPID
                slowVal = runPID(&slow); //updates slowVal, refernce misc.cpp
                runLift(slowVal);

                //debugging
                //std::cout << "liftPos: " << getLiftHeight() << " | slow.derivative: " << slow.derivative << " | slowVal: " << slowVal << std::endl;

            }

            else if(liftStat == LiftStatus::hold) {

                hold.error = (liftSetPoint - getLiftHeight()); //updates error for holdPID
                holdVal = runPID(&hold); //updates the holdVal, reference misc.cpp
                runLift(holdVal);

                //debugging
                //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | hold.error: " << hold.error << " | holdVal: " << holdVal << std::endl;

            }

            else if(liftStat == LiftStatus::move) {

                move.error = (liftSetPoint - getLiftHeight()); //updates error for movePID
                moveVal = runPID(&move); //updates the moveVal, reference misc.cpp
                runLift(moveVal);

                //debugging
                //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | move.error: " << move.error << " | moveVal: " << moveVal << std::endl;

            }

        }

        else { //reset the slow timer
            slowTimer = 300;
        }

        //prevents the lift motor from overheating
        liftSafetyNet();
        Task::delay_until(&now, 10);

    }

}

void setLiftHold(bool updateSetPoint) {

    //swiches to hold mode
    liftStat = LiftStatus::hold;
    //makes the lift hold the current position
    if(updateSetPoint)
        liftSetPoint = getLiftHeight();
    //resets any integral buildup
    resetIntegral = true;

}

void setLiftIdle() {

    liftStat = LiftStatus::idle;

}

void moveLift(int setPoint) {

    //sets the setPoint and initiates the PID to move to the setPoint
    liftSetPoint = setPoint;
    resetIntegral = true;
    liftStat = LiftStatus::move;

}

void queueLift(void* param) {

    //liftQueue* theQueue = static_cast<liftQueue*>(param);
    liftQueue* theQueue = (liftQueue*)param;
    int time = theQueue->queue, setPoint = theQueue->setPoint;
    for(int i = 0; i < time; i+=100)
        delay(100);
    moveLift(setPoint);

}

void moveLift(int setPoint, int queue) {

    //sets the setPoint and initiates the PID to move to the setPoint
    liftQueue newQueue = {setPoint, queue};
    std::cout << &newQueue << std::endl;
    std::cout << (&newQueue)->queue << " | " << (&newQueue)->setPoint << std::endl;
    Task delayLift(queueLift, &newQueue, TASK_PRIORITY_MIN, TASK_STACK_DEPTH_MIN, "lift movement task");
    delay(20);

}

void updateLift() {

    //if partner controller L1 or the master controller up, run the lift upwards
    if((l1Pressed(partner) && !r1Pressed(partner)) || (upPressed() && !downPressed())) {
        liftStat = LiftStatus::manual;
        runLift(100);
    }

    //if partner controller R1 or the master controller down, run the lift upwards
    else if((!l1Pressed(partner) && r1Pressed(partner)) || (!upPressed() && downPressed())) {
        liftStat = LiftStatus::manual;
        runLift(-100);
    }

    //skills tower heights
    else if(upPressed(partner)) {
        moveLift(onTower[2]);
    }

    else if(downPressed(partner)) {
        moveLift(onTower[1]);
    }

    else if(leftPressed(partner)) {
        moveLift(0);
    }

    //if the lift is low enough, it will drop down naturally so it won't tire out the motor
    else if(getLiftHeight() < 150 && liftSetPoint < 150)
        liftStat = LiftStatus::idle;

    //otherwise hold the lift's position
    else if(liftStat == LiftStatus::manual)
        liftStat = LiftStatus::slow;

}