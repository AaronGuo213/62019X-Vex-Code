#include "main.h"

void outtake() {

	trayStat = TrayStatus::manual;
    runIntk(0);
	while(getTrayPos() < 830) { //runs the tray forward until it is vertical
		runTray(calcTrayPow(1)); //updates tray power
		delay(50);
		if(getTrayPos() > 400) { //once the tray reaches a certain position
			leftIntk.set_brake_mode(E_MOTOR_BRAKE_COAST); //allows intake motors to be moved
    		rightIntk.set_brake_mode(E_MOTOR_BRAKE_COAST);
		}
	}
	runTray(0); //stops the tray

	//runBase(25, 25); //pushes the stack forward
	//delay(300);
	moveStraight(-10, 1, 1000, 60); //moves back
	leftIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    rightIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	runIntk(0);
	trayStat = TrayStatus::idle;

}