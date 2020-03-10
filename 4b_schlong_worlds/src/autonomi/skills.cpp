#include "main.h"

void skills() {

    //gets 3 cubes from the long L
    runIntk(100);
    moveTray(0);
    double distToCube = getSonarInches(10);
    if(distToCube > 26 || distToCube < 14)
        distToCube = 22;
    moveDist(distToCube + 1, 55);
    double minusThis = getDeployOffset(1500); //deploying tray
    moveDist(7 - minusThis, 50);
    delay(500);
    runIntk(0);

    //goes to the row of 4
    turnAbsolute(42, 60);
    setLiftIdle();
    setTrayIdle();
    delay(300);
    moveDist(-29);
    delay(300);
    turnAbsolute(0);
    delay(300);

    //gets the row of 4
    runIntk(100);
    moveDist(27, 40);
    delay(500);

    //outtakes
    moveDist(-18);
    delay(300);
    runIntkDist(-120, 150);
    delay(300);
    moveTray(400);
    delay(1500);
    runIntk(0);
    turnAbsolute(-135, 60);
    delay(300);
    moveDist(18, 70);
    outtakeSkills();

    //gets the medium tower
    moveTray(300);
    delay(1000);
    turnRelative(-270 - getAngle(), 60);
    moveTray(0);
    runIntk(100);
    moveDist(getSonarInches(10) - 2, 80);
    moveLift(onTower[2]);
    moveDist(-4);
    while(getLiftHeight() < onTower[2] - 100)
        delay(10);
    distToCube = getSonarInches(10);
    if(distToCube > 15 || distToCube < 0)
        distToCube = 10;
    moveDist(distToCube, 30);
    runIntk(-100);
    delay(300);
    moveDist(-10, 40);
    runIntk(0);
    moveLift(0);
    moveTray(300);
    delay(2000);

    //gets low tower
    moveDist(-9, 40);
    turnAbsolute(0);
    moveTray(0);
    delay(1000);
    runIntk(100);
    moveDist(getSonarInches(10), 80);
    moveLift(onTower[1]);
    moveDist(-8);
    while(getLiftHeight() < onTower[1] - 100)
        delay(10);
    distToCube = getSonarInches(10);
    if(distToCube > 15 || distToCube < 0)
        distToCube = 10;
    moveDist(distToCube, 60);
    runIntk(-100);
    delay(300);
    moveLift(0, 500);
    moveDist(-6, 30);
    runIntk(0);
    moveLift(0);

    //gets the cube from the pyramid
    delay(1000);
    turnAbsolute(-45);
    delay(300);
    runIntk(100);
    moveDist(17, 30);
    delay(1500);
    moveDist(-17, 100);

    //gets the alliance tower
    turnAbsolute(-100);
    moveLift(onTower[1]);
    delay(1000);
    moveDist(14, 70);
    runIntk(-100);
    delay(300);
    moveLift(0, 500);
    moveDist(-20, 80);
    runIntk(0);

}