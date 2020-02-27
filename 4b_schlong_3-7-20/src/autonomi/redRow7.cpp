#include "main.h"

void redRow7() {

    //deploys antitip
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10);
    if(distToCube > 19 || distToCube < 14)
        distToCube = 16;
    moveStraight(distToCube - 6.5, 40);
    //moveStraight(10, 40);
    moveLift(150);
    delay(500);
    moveLift(0);
    delay(500);

    //gets the row of 4
    moveStraight(10.5, 50);
    delay(1000);
    moveStraight(16, 50);
    setLiftIdle();

    //gets the 2 cubes under tower
    turnRelative(14, 50);
    moveStraight(12, 60);
    delay(300);
    turnRelative(-20, 50);
    moveStraight(8, 60);

    //goes to outtake
    moveStraight(-28, 100);
    runIntk(0);
    runIntkDist(-140, 150);
    delay(100);
    moveTray(400);
    delay(1000);
    runIntk(0);
    turnAbsolute(-135, 70);
    runBase(90);
    delay(800);
    runBase(0);
    delay(300);
    outtake();

    /*//deploys antitip
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
    curveBasePID(17, 18, 1400, 80);
    turn(-32, 0, 700);
    moveStraight(8, 0, 800);

    //goes to outtake
    moveStraight(-27, 0, 1300, 100);
    runIntk(0);
    turn(-119, 0, 1500, 70);
    runIntkDist(-180, 150);
    trayStat = TrayStatus::manual;
    runTray(80);
    moveStraight(19, 1, 1500, 80);
    outtake();*/

}