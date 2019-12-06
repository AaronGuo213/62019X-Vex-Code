#include "main.h"

void deploy() {

    liftStat = LiftStatus::manual;
    runLift(100);
    delay(300);
    runLift(0);
    runIntk(100);
    liftToGnd(50);
    runIntk(0);
    liftStat = LiftStatus::idle;
    delay(500);

}