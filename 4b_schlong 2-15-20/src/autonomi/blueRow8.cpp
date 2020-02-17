#include "main.h"

void blueRow8() {

    //deploys antitip
    moveStraight(12, 1, 700, 60);
    moveLift(150);
    delay(500);
    moveLift(0);
    moveTray(0);

    //intakes the first 2 cubes, gets the 2 stack in the intake
    runIntk(100);
    moveStraight(15, 0, 1500, 60);
    setLiftIdle();
    setTrayIdle();
    runIntk(100, 500);
    delay(1000);
    moveStraight(7, 0, 600, 80);

    //knocks the top cube to the side and intakes the bottom cube, goes to row
    runIntk(100);
    turn(-45, 0, 900, 70);
    runIntk(0);
    moveStraight(-31, 0, 1200, 100);
    turn(45, 0, 900, 70);

    //intakes 4 cubes from the row
    runIntk(100);
    moveStraight(28, 0, 2000, 55);
    runIntk(100, 500);
    moveStraight(-15, 0, 800);

    //spits cube to position to outtake and turns
    runIntkDist(-140, 150);
    turn(120, 0, 1500, 70);

    //preemtively puts the tray up for outtaking and moves to the goal
    trayStat = TrayStatus::manual;
    runTray(100);
    moveStraight(12, 1, 1000, 70);
    outtake();

}