#include "main.h"

void redStack8() {

    //gets the first cube
    runIntk(100);
    moveTray(0);
    moveStraight(22, 70);
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
    delay(1500);
    liftStat = LiftStatus::manual;
    liftToGnd(-30);
    while(getLiftHeight() > atCube[2] - 50)
        delay(10);
    moveStraight(8, 80);
    setTrayIdle();

    //gets the bottom of the 4 stack and the cube at the tower
    turnRelative(20);
    moveStraight(12);

    //gets the cube next to the goal and outtakes
    turnAbsolute(135, 70);
    runIntk(100);
    moveStraight(36, 30, 1, 1800, 80, 40);
    trayStat = TrayStatus::manual;
    runIntk(0);
    delay(100);
    runIntkDist(-180, 150);
    delay(200);
    runTray(100);
    //moveStraight(-2, 0, 1000, 60);
    delay(1000);
    outtake();

}