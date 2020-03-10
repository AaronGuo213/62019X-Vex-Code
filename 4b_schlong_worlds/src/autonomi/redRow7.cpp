#include "main.h"

void redRow7() {

    //deploys antitip
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10, 22, 14, 26);
    moveDist(distToCube, 65);

    //gets the first 2 cubes of the long L
    double minusThis = getDeployOffset(1500); //deploying tray
    runIntk(0);

    //moves to and gets the row of 4
    turnRelative(55, 70);
    //moveDist(-29);
    moveDist(-27);
    turnAbsolute(0);
    runIntk(100);
    //moveDist(27 - minusThis, 50);
    moveDist(23 - minusThis, 50);
    delay(500);

    //outtakes
    runIntkDist(-150, 150);
    delay(300);
    moveTray(400);
    moveDist(-15);
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
    moveDist(-40, 60);

}