#include "main.h"

void redStack8() {

    //gets the first cube
    runIntk(100);
    moveTray(0);
    moveStraight(21, 80);
    runIntk(0);

    //gets the 4 stack
    moveLift(atCube[4]);
    while(getLiftHeight() < atCube[4] - 50)
        delay(50);
    runIntk(100);
    double distToCube = getSonarInches(10);
    if(distToCube > 12 || distToCube < 4)
        distToCube = 8;
    moveStraight(distToCube - 3, 30);
    double minusThis = getDeployOffset(1500);
    liftStat = LiftStatus::manual;
    liftToGnd(-30);
    while(getLiftHeight() > atCube[2] - 50)
        delay(10);
    moveTray(150);
    moveStraight(8 - minusThis, 80);
    delay(200);

    //gets the bottom of the 4 stack and the cube at the tower
    turnRelative(20);
    moveStraight(12, 70);
    runIntk(0);

    //gets the cube next to the goal and outtakes
    turnAbsolute(135, 70);
    runIntk(100);
    moveStraight(36, 30, 0, 1800, 100, 40);
    trayStat = TrayStatus::manual;
    runIntk(0);
    delay(100);
    runIntkDist(-150, 150);
    delay(200);
    runTray(100);
    //moveStraight(-2, 0, 1000, 60);
    delay(500);
    outtake();

}