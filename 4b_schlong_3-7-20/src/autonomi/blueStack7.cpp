#include "main.h"

void blueStack7() {

    //gets the first cube
    runIntk(100);
    moveTray(0);
    moveStraight(22, 100);
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
    //moveStraight(5, 0, 2500, 30);
    liftStat = LiftStatus::manual;
    liftToGnd(-30);
    while(getLiftHeight() > atCube[2] - 50)
        delay(10);
    moveStraight(8, 80);
    setTrayIdle();

    //gets the cube next to the goal
    turnRelative(-110, 70);
    setLiftIdle();
    moveStraight(25, 80);
    delay(500);

    //outtakes
    runIntk(0);
    delay(100);
    runIntkDist(-120, 150);
    delay(100);
    moveTray(400);
    delay(1000);
    turnAbsolute(-135);
    runBase(50);
    delay(600);
    runBase(0);
    outtake();

}