#include "main.h"

void redRow6() {

    //deploys antitip
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10);
    if(distToCube > 19 || distToCube < 14)
        distToCube = 16;
    moveDist(distToCube - 6.5, 40);
    //moveDist(10, 40);
    moveLift(150);
    delay(500);
    moveLift(0);
    delay(500);

    //gets the row of 4
    moveDist(10.5, 50);
    delay(1500);
    moveDist(16, 50);
    setLiftIdle();

    //gets the cube under tower
    turnRelative(12, 100);
    moveDist(14, 60);

    //goes to outtake
    moveDist(-32, 100);
    runIntk(0);
    runIntkDist(-140, 150);
    delay(100);
    moveTray(400);
    delay(1000);
    runIntk(0);
    turnAbsolute(-135, 70);
    runBase(60);
    delay(600);
    runBase(0);
    outtake();
    moveTray(0);
    moveDist(-40, 60);

}