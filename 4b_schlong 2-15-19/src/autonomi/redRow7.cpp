#include "main.h"

void redRow7() {

    runIntk(100);
    moveStraight(5, 0, 1000, 70);
    moveLift(150);
    delay(600);
    moveLift(0);
    moveStraight(25, 0, 2000, 50);
    curveBasePID(20, 21, 1800, 80);
    curveBasePID(8, 4, 1000, 80);
    moveStraight(-30, 0, 2000, 80);
    runIntk(0);
    turn(-90, 0, 1500, 70);
    runIntkDist(-120, 50);
    trayStat = TrayStatus::manual;
    runTray(80);
    moveStraight(20, 1, 1500, 80);
    outtake();

}