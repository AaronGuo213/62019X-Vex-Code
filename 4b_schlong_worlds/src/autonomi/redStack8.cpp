#include "main.h"

void redStack8() {

    //gets the first cube
    runIntk(100);
    moveTray(0);
    moveDist(19, 100);
    runIntk(0);

    //gets the 4 stack
    moveLift(atCube[4]);
    while(getLiftHeight() < atCube[4] - 50)
        delay(50);
    runIntk(100);
    double distToCube = getSonarInches(10, 8, 4, 12);
    moveDist(distToCube - 3, 30);
    delay(1000);
    liftStat = LiftStatus::manual;
    liftToGnd(-40);
    double minusThis = 0;//getDeployOffset(500);
    while(getLiftHeight() > atCube[2] - 50)
        delay(10);
    //moveTray(200);
    moveDist(8 - minusThis, 100);
    //delay(300);

    //gets the bottom of the 4 stack and the cube at the tower
    turnAbsolute(15);
    moveDist(14, 80);
    delay(300);

    //gets the cube next to the goal and outtakes
    turnAbsolute(135, 70);
    runIntk(100);
    moveDist(30, 1, 2000, 100);
    delay(300);
    runIntkDist(-180, 150);
    trayStat = TrayStatus::manual;
    runTray(100);
    runBase(30);
    //moveDist(-2, 0, 1000, 60);
    delay(700);
    runBase(0);
    outtake();
    moveTray(0);
    moveDist(-40, 60);

}