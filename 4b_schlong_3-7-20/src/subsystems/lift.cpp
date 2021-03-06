#include "main.h"

const int atCube[] = {0, 0, 250, 500, 600, 850}; //array for cube heights
const int onTower[] = {620, 600, 840}; //array for tower heights

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
double liftVel = 0; //how fast the lift motor runs in rpm
bool resetIntegral = false; //determines when to reset the integral buildup

void ctrlLift(void* param) {

    std::uint32_t now = millis();
    PID hold = initPID(1, 1, 0, 1.2, 0.0008, 0); //kP = 1.2, kI = 0.0008
    PID slow = initPID(0, 0, 1, 0, 0, 0.6); //kD = 0.6
    PID move = initPID(1, 1, 1, 1.8, 0.00048, 6); //kP = 1.8, kI = 0.00048, kD = 6
    double holdVal = 0, slowVal = 0, moveVal = 0;
    int slowTimer = 300; //slows for 300ms

    while(true) {

        liftSetPoint = liftSetPoint > 840 ? 840 : liftSetPoint; //lift cannot be higher than 840
        liftSetPoint = liftSetPoint < 0 ? 0 : liftSetPoint; //lift cannot be lower than 0

        if(resetIntegral) { //prevents integral windup
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

                slow.error = -getLiftHeight(); //updates error and motor value for slowPID
                slowVal = runPID(&slow);
                runLift(slowVal);

                //debugging
                //std::cout << "liftPos: " << getLiftHeight() << " | slow.derivative: " << slow.derivative << " | slowVal: " << slowVal << std::endl;

            }

            else if(liftStat == LiftStatus::hold) {

                hold.error = (liftSetPoint - getLiftHeight()); //updates error and motor value for holdPID
                holdVal = runPID(&hold);
                runLift(holdVal);

                //debugging
                //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | hold.error: " << hold.error << " | holdVal: " << holdVal << std::endl;

            }

            else if(liftStat == LiftStatus::move) {

                move.error = (liftSetPoint - getLiftHeight()); //updates error and motor value for movePID
                moveVal = runPID(&move);
                runLift(moveVal);

                //debugging
                //std::cout << "liftSetPoint: " << liftSetPoint << " | liftPos: " << getLiftHeight() << " | move.error: " << move.error << " | moveVal: " << moveVal << std::endl;

            }

        }

        else { //other options in the manual mode

            if(liftVel != 0) {
                
                if(getLiftHeight() > 50) {
                    lift.move_velocity(-abs(liftVel)); //lift moves down at certain speed
                }

                else { //once it reaches the threshhold the lift stops
                    runLift(0);
                    liftVel = 0;
                }

            }

            slowTimer = 300; //resets slow timer

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

    //waits for a given time before moving the lift to a certain height
    liftQueue* theQueue = (liftQueue*)param;
    int time = theQueue->queue, setPoint = theQueue->setPoint;
    for(int i = 0; i < time; i+=10)
        delay(10);
    moveLift(setPoint);

}

void moveLift(int setPoint, int queue) {

    //sets up for the task for moving the lift after a certain time
    liftQueue newQueue = {setPoint, queue};
    Task delayLift(queueLift, &newQueue, TASK_PRIORITY_MIN, TASK_STACK_DEPTH_MIN, "lift movement task");
    delay(20);

}

void liftToGnd(double percentSpeed) {

    //sets up the lift task to move the lift down to the ground
    liftStat = LiftStatus::manual;
    liftVel = percentSpeed * 2; //100 percent goes to 200 rpm

}

void updateLift() {

    //if partner controller L1 or the master controller up, run the lift upwards
    /*if(((!l2Pressed(partner) && r2Pressed(partner)) || (upPressed() && !downPressed())) && (getLiftHeight() < 900)) {
        liftStat = LiftStatus::manual;
        runLift(100);
    }

    //if partner controller R1 or the master controller down, run the lift upwards
    else if(((l2Pressed(partner) && !r2Pressed(partner)) || (!upPressed() && downPressed())) && (getLiftHeight() > 50)) {
        liftStat = LiftStatus::manual;
        runLift(-100);
    }*/

    //L2 moves the lift up if the lift is lower than max height
    if(l2Pressed() && !r2Pressed() && getLiftHeight() < 900) {
        liftStat = LiftStatus::manual;
        runLift(100);
    }

    //R2 moves the lift down if the lift is higher than minimum height
    else if(!l2Pressed() && r2Pressed() && getLiftHeight() > 50) {
        liftStat = LiftStatus::manual;
        runLift(-100);
    }

    //if the lift is low enough, it will drop down naturally so it won't tire out the motor
    else if(getLiftHeight() < 150 && liftSetPoint < 150)
        liftStat = LiftStatus::idle;

    //otherwise hold the lift's position
    else if(liftStat == LiftStatus::manual)
        liftStat = LiftStatus::slow;

}