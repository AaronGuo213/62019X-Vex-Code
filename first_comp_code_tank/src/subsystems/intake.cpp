#include "main.h"

void runClaw(float percentage, int time) {

    clawVal = percentage;
    runTime = time;

}

float clawVal;
int runTime;

void clawCtrl(void* param) {

    while(true) {

        if(runTime > 0) {

            claw1.move_voltage(clawVal * 120);
            runTime -= 1;

        }

        else
            claw1.move_voltage(0);

        delay(1);

    }

}