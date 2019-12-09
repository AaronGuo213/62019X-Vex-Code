#include "main.h"

void red4Stack() {

    //gets the first cube
    runIntk(100);
    moveStraight(18, 1400);
    runIntk(0);

    //gets the cubes from the 4 stack
    moveLift(atCube[5]);
    delay(2000);
    moveStraight(5, 1000, 60);
    runIntk(100);
    liftStat = LiftStatus::manual;
    runLift(0);
    delay(500);
    runLift(5);
    delay(200);
    runLift(0);
    delay(500);
    runLift(5);
    delay(200);
    runLift(0);
    delay(500);
    moveStraight(5, 1000, 60);
    runIntk(0);

    //gets the cube next to the tower
    turn(1.3, 1000);
    runIntk(100);
    moveStraight(15, 1500);
    runIntk(0);

    //gets the stray cube near the goal
    turn(5.3, 1500, 80);
    runIntk(100);
    moveStraight(36, 2200);
    runIntk(-25);
    delay(500);
    runIntk(0);
    trayStat = TrayStatus::manual;
    runTray(100);

    //outtakes
    outtake(0);

}