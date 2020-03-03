#include "main.h"

void blueRow7() {

    //deploys antitip
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10);
    if(distToCube > 26 || distToCube < 14)
        distToCube = 22;
    //moveLift(150);
    //moveLift(0, 500);
    moveStraight(distToCube - 8);

    //gets the first 2 cubes of the long L
    moveStraight(10.5, 60);
    delay(1500); //deploying tray
    runIntk(0);

    //moves to and gets the row of 4
    turnRelative(-60, 70);
    moveStraight(-27);
    turnAbsolute(0, 70);
    runIntk(100);
    moveStraight(27, 50);

    //outtakes
    moveStraight(-15);
    runIntkDist(-120, 150);
    moveTray(400);
    delay(900);
    runIntk(0);
    turnAbsolute(135);
    runBase(100);
    delay(400);
    runBase(0);
    delay(200);
    outtake();

}