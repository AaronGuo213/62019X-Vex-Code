#include "main.h"

void runLift(float percentage) {

    lift1.move_voltage(percentage * 120);
    lift2.move_voltage(percentage * 120);

}

bool manual = false, manualUsed = false, shiftUp = false, shiftDown = false, reset = false;
int height = 0, setPoint;

void liftCtrl(void* param) {

    PID lift = initPID(0, 0, 0, 0, 0, 0);
    int aboveCube[5] = {0, 10, 20, 30, 40};
    setPoint = aboveCube[height];
    int liftVal;

    while(!manual) {
        
        if(reset) {
            reset = false;
            height = 0;
            setPoint = aboveCube[height];
        }

        if(!manualUsed) {

            if(shiftUp) {
                shiftUp = false;
                if(height < 4)
                    height++;
                setPoint = aboveCube[height];
            }

            else if(shiftDown) {
                shiftDown = false;
                if(height > 0)
                    height--;
                setPoint = aboveCube[height];
            }

        }

        else if(manualUsed) {

            if(shiftUp) {

                for(int i = 0; i < 5; i++) {

                    if(setPoint < aboveCube[i])
                        height = i;
                    break;

                }

                setPoint = aboveCube[height];
                manualUsed = false;

            }

            else if(shiftDown) {

                for(int i = 4; i >= 0; i--) {

                    if(setPoint > aboveCube[i])
                        height = i;
                    break;

                }

                setPoint = aboveCube[height];
                manualUsed = false;

            }

        }

        if(lift2.is_over_temp() || lift2.is_over_current())
			lift2.set_voltage_limit(0);
		else
			lift2.set_voltage_limit(12000);

        lift.error = setPoint - liftPot.get_value();
        liftVal = runPID(&lift);
        runLift(liftVal);

        delay(1);

    }

    if(manual) {

        setPoint = liftPot.get_value();

        if(lift2.is_over_temp() || lift2.is_over_current())
			lift2.set_voltage_limit(0);
		else
			lift2.set_voltage_limit(12000);

        shiftUp = false;
        shiftDown = false;
        manualUsed = true;

    }

}

/*void shiftLift(int direction) {

    int level [5] = {0, 10, 20, 30, 40};
    float error, liftVal, setPoint;
    int threshhold = 5;
    PID lift = initPID(0, 0, 0, 0, 0, 0);
    lift.error = threshhold + 1;

    if(direction > 0) {

        for(int i = 4; i > -1; i--) {

            if(liftPot.get_value() + 5 < level[i]) {
                setPoint = level[i - 1];
                break;
            }

        }

        while(lift.error > 5) {

            lift.error

        }

    }

    else if(direction < 0) {

        for(int i = 0; i < 5; i++) {

            if(nowLevel > level[i]) {

                while(liftPot.get_value() + 5 < level[i - 1]) {
                    
                    error = level[i - 1] - liftPot.get_value();
                    liftVal = P * error;
                    runLift(liftVal);

                }

                break;

            }

        }

    }

}*/