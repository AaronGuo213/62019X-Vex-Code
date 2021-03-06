#include "main.h"

void deploy() {

    liftStat = LiftStatus::idle;
    moveTray(200);
    delay(500);
	tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
	trayStat = TrayStatus::idle;
	delay(500);
    runIntk(100);
	delay(1000);
	runIntk(0);

}

void outtake(double intkSpeed) {

	trayStat = TrayStatus::manual;
    runIntk(0);
	while(getTrayPos() < 940) { //runs the tray forward until it is vertical
		runTray(calcTrayPow(1) + 20);
		delay(50);
		if(getTrayPos() > 400) {
			leftIntk.set_brake_mode(E_MOTOR_BRAKE_COAST);
    		rightIntk.set_brake_mode(E_MOTOR_BRAKE_COAST);
		}
	}
	runTray(0);

	//if(intkSpeed) //if requested, the intake will run outwards
		//runIntk(-intkSpeed);
	runLeftBase(25); //pushes the stack forward
	runRightBase(25);
	delay(300);
	moveStraight(-15, 1000, 60); //moves back
	runIntk(0);
	runTray(0);
	trayStat = TrayStatus::idle;

}