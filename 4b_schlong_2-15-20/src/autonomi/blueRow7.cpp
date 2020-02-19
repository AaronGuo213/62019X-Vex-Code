#include "main.h"

void blueRow7() {

    //deploys antitip
    runIntk(100);
    moveTray(0);
    moveStraight(7, 0, 700, 70);
    moveLift(150);
    delay(500);
    moveLift(0);

    //gets the first 2 cubes and deploys tray
    runIntk(100);
    moveStraight(13, 0, 2000, 50);

    //gets the last 2 cubes from the row
    moveStraight(10, 0, 1000, 50);
    setLiftIdle();

    //gets the 2 cubes under tower
    curveBasePID(18, 17, 1400, 80);
    turn(32, 0, 700);
    moveStraight(8, 0, 800);

    //goes to outtake
    moveStraight(-27, 0, 1300, 100);
    runIntk(0);
    turn(119, 0, 1500, 70);
    runIntkDist(-180, 150);
    trayStat = TrayStatus::manual;
    runTray(80);
    moveStraight(19, 1, 1500, 80);
    outtake();

}