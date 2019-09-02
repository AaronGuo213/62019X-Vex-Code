#include "main.h"

void runLift(float percentage) {

    /*lift1.move_voltage(percentage * 120);
    lift2.move_voltage(percentage * 120);*/

    lift1.move_velocity(percentage * 2);
    lift2.move_velocity(percentage * 2);

}

void runClaw(float percentage) {

    claw1.move_voltage(percentage * 120);

}

bool manual = false, manualUsed = false, shiftUp = false, shiftDown = false, reset = false;
int height = 0, liftSetPoint;
int aboveCube[5] = {1110, 1560, 1910, 2320, 2930}; //array of potentiometer values that correspond with heights above certain number of cubes

void liftCtrl(void* param) {

    PID lift = initPID(1, 1, 0, 0.2, 0.0001, 0); //kP = 0.2, kI = 0.0001
    liftSetPoint = aboveCube[height];
    float liftVal;

    while(true) { //runs continuously the whole match

    if(!manual) {
        
        if(reset) {
            reset = false;
            height = 0; //changes the height of the lift to above 0 cubes
            liftSetPoint = aboveCube[height];
        }

        if(!manualUsed) { //if the lift is at a certain value of the aboveCube array

            if(shiftUp) {
                shiftUp = false;
                if(height < 4) //if the lift is still able to move up
                    height++;
                liftSetPoint = aboveCube[height]; //update the liftSetPoint
            }

            else if(shiftDown) {
                shiftDown = false;
                if(height > 0) //if the lift is still able to move down
                    height--;
                liftSetPoint = aboveCube[height]; //update the liftSetPoint
            }

        }

        else if(manualUsed) { //if the lift needs to move to the nearest value of the aboveCube array

            if(shiftDown) {

                for(int i = 0; i < 5; i++) { //finds the closest height that is still less than the current value

                    if(liftSetPoint < aboveCube[i])
                        height = i;
                    break;

                }

                liftSetPoint = aboveCube[height];
                manualUsed = false;

            }

            else if(shiftUp) {

                for(int i = 4; i >= 0; i--) { //finds the closest height that is still greater than the current height

                    if(liftSetPoint > aboveCube[i])
                        height = i;
                    break;

                }

                liftSetPoint = aboveCube[height];
                manualUsed = false;

            }

        }

        if(lift2.is_over_temp() || lift2.is_over_current()) //prevents the motors from burning out or overheating
			lift2.set_voltage_limit(0);
		else
			lift2.set_voltage_limit(12000);

        lift.error = liftSetPoint - liftPot.get_value(); //updates the error for the liftPID
        liftVal = runPID(&lift); //updates the value for the liftPID, reference misc.cpp
        runLift(-liftVal);

        std::cout << liftSetPoint << " | " << liftPot.get_value() << " | " << lift.error << "\n";

    }

    else if(manual) { //allows the driver to control the lift completely

        liftSetPoint = liftPot.get_value();

        if(lift2.is_over_temp() || lift2.is_over_current())
			lift2.set_voltage_limit(0); //prevents overheating or burning out of motors
		else
			lift2.set_voltage_limit(12000);

        shiftUp = false;
        shiftDown = false;
        manualUsed = true;

    }

    delay(1);

    }

}

void autostack(int cubes) {

    int sonarDist = 0;

    if(!manualUsed) {

        int heightF = height - cubes;

        while(!cubeSensor.get_value() == 0) { //uses a P loop to move to the correct distance from the cube
            runLeftBase1((sonarDist - cubeSensor.get_value()) * 0);
            runLeftBase2((sonarDist - cubeSensor.get_value()) * 0);
            runRightBase1((sonarDist - cubeSensor.get_value()) * 0);
            runRightBase2((sonarDist - cubeSensor.get_value()) * 0);
        }

        runClaw(-100); //opens claw
        delay(300);
        liftSetPoint = aboveCube[heightF >= 0 ? heightF : 0]; //checks if the lift is high enough above the next cube to stack

        while(abs(liftPot.get_value() - liftSetPoint) > 10) { //runs the P loop again while the lift is reaching to correct height
            if(!cubeSensor.get_value() == 0) {
                runLeftBase1((sonarDist - cubeSensor.get_value()) * 0);
                runLeftBase2((sonarDist - cubeSensor.get_value()) * 0);
                runRightBase1((sonarDist - cubeSensor.get_value()) * 0);
                runRightBase2((sonarDist - cubeSensor.get_value()) * 0);
            }
        }

        runClaw(100); //closes the claw on the whole stack
        delay(300);

    }

}