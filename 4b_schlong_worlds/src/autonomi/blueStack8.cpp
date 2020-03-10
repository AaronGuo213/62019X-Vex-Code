#include "main.h"

void blueStack8() {

    //gets the first cube
    runIntk(100);
    delay(200);
    moveTray(0);
    moveDist(19, 100);
    runIntk(0);

    //gets the 4 stack
    moveLift(atCube[4]);
    while(getLiftHeight() < atCube[4] - 50)
        delay(50);
    runIntk(100);
    double distToCube = getSonarInches(10);
    if(distToCube > 12 || distToCube < 4)
        distToCube = 8;
    moveDist(distToCube - 3, 30);
    delay(700);
    double minusThis = 0;
    liftStat = LiftStatus::manual;
    liftToGnd(-30);
    while(getLiftHeight() > atCube[2] - 50)
        delay(10);
    moveDist(8 - minusThis, 100);
    //delay(300);

    //gets the bottom of the 4 stack and the cube at the tower
    turnAbsolute(-15);
    moveDist(14, 80);
    delay(300);

    //gets the cube next to the goal and outtakes
    turnAbsolute(-135, 70);
    runIntk(100);
    moveStraight(18, 100);
    trayStat = TrayStatus::manual;
    runTray(100);
    moveStraight(7, 100);
    runTray(40);
    runBase(70);
    delay(300);
    runBase(0);
    delay(500);
    runTray(100);
    runIntkDist(-120, 150);
    runBase(-20);
    delay(200);
    runBase(0);
    delay(400);
    outtake();
    moveTray(0);
    moveDist(-40, 60);

}