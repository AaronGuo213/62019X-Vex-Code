#include "main.h"

void skills() {

    //gets 3 cubes from the long L
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10);
    if(distToCube > 26 || distToCube < 14)
        distToCube = 22;
    moveStraight(distToCube + 1, 55);
    double minusThis = getDeployOffset(1500); //deploying tray
    moveStraight(7 - minusThis, 50);
    delay(500);
    runIntk(0);

    //goes to the row of 4
    turnAbsolute(50, 70);
    setLiftIdle();
    setTrayIdle();
    delay(300);
    moveStraight(-29);
    delay(300);
    turnAbsolute(0);
    delay(300);

    //gets the row of 4
    runIntk(100);
    moveStraight(27, 40);
    delay(500);

    //outtakes
    moveStraight(-18);
    delay(300);
    runIntkDist(-120, 150);
    delay(300);
    moveTray(400);
    delay(1500);
    runIntk(0);
    turnAbsolute(-135, 60);
    delay(300);
    moveStraight(18, 70);
    outtakeSkills();

    //gets the medium tower
    moveTray(300);
    delay(1000);
    turnRelative(-270 - getAngle(), 60);
    moveTray(0);
    runIntk(100);
    moveStraight(getSonarInches(10) - 2, 80);
    moveLift(onTower[2]);
    moveStraight(-4);
    while(getLiftHeight() < onTower[2] - 100)
        delay(10);
    distToCube = getSonarInches(10);
    if(distToCube > 15 || distToCube < 0)
        distToCube = 10;
    moveStraight(distToCube, 30);
    runIntk(-100);
    delay(300);
    moveStraight(-10, 40);
    runIntk(0);
    moveLift(0);
    moveTray(300);
    delay(2000);

    //gets low tower
    moveStraight(-9, 40);
    turnAbsolute(0);
    moveTray(0);
    delay(1000);
    runIntk(100);
    moveStraight(getSonarInches(10), 80);
    moveLift(onTower[1]);
    moveStraight(-8);
    while(getLiftHeight() < onTower[1] - 100)
        delay(10);
    distToCube = getSonarInches(10);
    if(distToCube > 15 || distToCube < 0)
        distToCube = 10;
    moveStraight(distToCube, 60);
    runIntk(-100);
    delay(300);
    moveLift(0, 500);
    moveStraight(-6, 30);
    runIntk(0);
    moveLift(0);

    //gets the cube from the pyramid
    delay(1000);
    turnAbsolute(-45);
    delay(300);
    runIntk(100);
    moveStraight(17, 30);
    delay(1500);
    moveStraight(-17, 100);

    //gets the alliance tower
    turnAbsolute(-100);
    moveLift(onTower[1]);
    delay(1000);
    moveStraight(14, 70);
    runIntk(-100);
    delay(300);
    moveLift(0, 500);
    moveStraight(-20, 80);
    runIntk(0);

}