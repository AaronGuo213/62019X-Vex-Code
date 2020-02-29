#include "main.h"

void redRow7() {

    //deploys antitip
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10);
    if(distToCube > 26 || distToCube < 18)
        distToCube = 22;
    moveLift(150);
    moveLift(0, 500);
    moveStraight(distToCube - 8);

    //gets the first 2 cubes of the long L
    moveStraight(10.5, 60);
    delay(1500); //deploying tray
    runIntk(0);

    //moves to and gets the row of 4
    turnRelative(60, 70);
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
    turnAbsolute(-135);
    runBase(100);
    delay(400);
    runBase(0);
    delay(200);
    outtake();

    /*//deploys antitip
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10);
    if(distToCube > 19 || distToCube < 14)
        distToCube = 16;
    moveStraight(distToCube - 6.5, 40);
    //moveStraight(10, 40);
    moveLift(150);
    delay(500);
    moveLift(0);
    delay(500);

    //gets the row of 4
    moveStraight(10.5, 50);
    delay(1000);
    moveStraight(16, 50);
    setLiftIdle();

    //gets the 2 cubes under tower
    turnRelative(14, 50);
    moveStraight(12, 60);
    delay(300);
    turnRelative(-20, 50);
    moveStraight(8, 60);

    //goes to outtake
    moveStraight(-28, 100);
    runIntk(0);
    runIntkDist(-140, 150);
    delay(100);
    moveTray(400);
    delay(1000);
    runIntk(0);
    turnAbsolute(-135, 70);
    runBase(90);
    delay(800);
    runBase(0);
    delay(300);
    outtake();*/

}