#include "main.h"

void blueStack7() {

    //gets the first cube
    runIntk(100);
    moveTray(0);
    moveStraight(22, 0, 1300, 70);
    runIntk(0);

    //gets the 4 stack
    moveLift(atCube[4]);
    delay(1500);
    runIntk(100);
    moveStraight(4, 0, 2500, 30);
    liftStat = LiftStatus::manual;
    lift.move_velocity(-50);
    while(getLiftHeight() > 70)
        delay(10);
    setLiftIdle();
    setTrayIdle();
    moveStraight(10, 0, 1000, 60);

    //gets the last cube next to the goal and outtakes
    turn(-110, 0, 1400, 60);
    moveStraight(15, 0, 1000, 80);
    runIntkDist(-160, 150);
    delay(300);
    trayStat = TrayStatus::manual;
    runTray(80);
    curveBaseVel(18, 17, 1500, 80);
    outtake();

}