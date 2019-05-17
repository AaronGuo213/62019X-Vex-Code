#include "main.h"

void runLift(float percentage) {

    lift1.move_voltage(percentage * 120);
    lift2.move_voltage(percentage * 120);

}

void shiftLift(int direction) {

    int level [5] = {0, 10, 20, 30, 40};
    int nowLevel = liftPot.get_value();
    int error, P = 0, liftVal;

    if(direction > 0) {

        for(int i = 4; i > -1; i--) {

            if(nowLevel < level[i]) {

                while(liftPot.get_value() + 5 < level[i + 1]) {
                    
                    error = level[i + 1] - liftPot.get_value();
                    liftVal = P * error;
                    runLift(liftVal);

                }

                break;

            }

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

}