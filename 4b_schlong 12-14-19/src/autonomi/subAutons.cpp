#include "main.h"

void deploy() {

    //liftStat = LiftStatus::manual;
    runLift(0);
    trayStat = TrayStatus::manual;
    runTray(100);
    delay(500);
    runLeftBase(-50);
    runRightBase(-50);
    runTray(-100);
    runIntk(50);
    //runLift(-100);
    delay(1500);
    trayStat = TrayStatus::idle;
    liftStat = LiftStatus::idle;

}

void outtake(double intkSpeed) {

	trayStat = TrayStatus::manual;
	while(getTrayPos() < 920) { //runs the tray forward until it is vertical
		runTray(calcTrayPow(1) + 23);
		delay(50);
	}
	runTray(0);

	if(intkSpeed) //if requested, the intake will run outwards
		runIntk(-intkSpeed);
	runLeftBase(25); //pushes the stack forward
	runRightBase(25);
	delay(300);
	moveStraight(-15, 1000, 80); //moves back
	runIntk(0);
	runTray(0);
	trayStat = TrayStatus::idle;

}