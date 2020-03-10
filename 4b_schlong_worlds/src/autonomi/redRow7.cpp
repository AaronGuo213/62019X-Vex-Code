#include "main.h"

void redRow7() {

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
    turnRelative(55, 70);
    //moveStraight(-29);
    moveStraight(-27);
    turnAbsolute(0);
    runIntk(100);
    //moveStraight(27 - minusThis, 50);
    moveStraight(23 - minusThis, 50);
    delay(500);

    //outtakes
    runIntkDist(-150, 150);
    delay(300);
    moveTray(400);
    moveStraight(-15);
    runIntk(0);
    delay(100);
    turnAbsolute(-135, 80);
    delay(100);
    runBase(100);
    delay(400);
    runBase(0);
    //delay(200);
    outtake();
    moveTray(0);
    moveStraight(-40, 60);

}