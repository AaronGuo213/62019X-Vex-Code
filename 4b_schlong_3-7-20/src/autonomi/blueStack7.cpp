#include "main.h"

void blueStack7() {

    //gets the first cube
    runIntk(100);
    delay(200);
    moveTray(0);
    moveStraight(19, 100);
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
    moveStraight(8 - minusThis, 80);
    delay(300);
    setTrayIdle();

    //gets the cube next to the goal
    turnRelative(-110, 70);
    setLiftIdle();
    moveStraight(23, 80);
    delay(500);

    //outtakes
    runIntk(0);
    delay(100);
    runIntkDist(-150, 150);
    turnAbsolute(-132);
    runIntk(0);
    trayStat = TrayStatus::manual;
    runTray(100);
    runBase(30);
    delay(850);
    runBase(-20);
    delay(180);
    runBase(0);
    outtake();

}