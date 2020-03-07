#include "main.h"

void blueRow7() {

    //deploys antitip
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10);
    if(distToCube > 26 || distToCube < 14)
        distToCube = 22;
    moveStraight(distToCube, 65);

    //gets the first 2 cubes of the long L
    double minusThis = getDeployOffset(1500); //deploying tray
    runIntk(0);

    //moves to and gets the row of 4
    /*turnRelative(60, 70);
    moveStraight(-27);
    turnAbsolute(0, 70);*/
    turnRelative(-55, 70);
    moveStraight(-29);
    turnAbsolute(0);
    runIntk(100);
    moveStraight(27 - minusThis, 50);
    delay(500);

    //outtakes
    runIntkDist(-150, 150);
    delay(300);
    moveTray(400);
    moveStraight(-14);
    runIntk(0);
    delay(500);
    turnAbsolute(135, 80);
    runBase(100);
    delay(400);
    runBase(0);
    delay(200);
    outtake();

}