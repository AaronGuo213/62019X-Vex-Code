#include "main.h"

void runIntk(double percent) {

    leftIntk.move_voltage(percent * 120);
	rightIntk.move_voltage(percent * 120);

}

void updateIntk() {

    if(l1() && !r1()) //l1 pressed runs intake inwards
		runIntk(100);

	else if(r1() && !l1()) //l2 pressed runs intake outwards
		runIntk(-100);

	else //otherwise dont run the intake
		runIntk(0);

}

void runTray(double percent) {

    tray.move_voltage(percent * 120);
	
}

int getTrayPos() {

	return tray.get_position() - 0;
		
}

 //calculates the power to send to the tray motor for a consistent outtaking process
double calcTrayPow(bool moveForward) {

	if(moveForward) {
		return getTrayPos();
	}

	return -1000 + getTrayPos();

}

void updateTray() {

	if(r2() && !l2())
		runTray(100);
	
	else if(l2() && !r2())
		runTray(-100);

	else 
		runTray(0);

	/*if(r1() && !r2()) { //r1 pressed runs the tray outward
		runTray(calcTrayPow(1));
	}

	else if(r2() && !r1()) { //r2 pressed runs the tray inward
		runTray(calcTrayPow(0));
	}

	else //otherwise dont run the tray motor
		runTray(0);*/

	/*if(r1() && !r2()) {
		if(trayStat == trayStatus::retract || trayStat == trayStatus::idle)
			trayStat = trayStatus::outtake;
		else if(trayStat == trayStatus::outtake || trayStat == trayStatus::hold)
			trayStat = trayStatus::retract;
	}*/

}

void outtake(double intkSpeed) {

	leftIntk.set_brake_mode(E_MOTOR_BRAKE_COAST); //lets the cubes slide down the intake slowly
	rightIntk.set_brake_mode(E_MOTOR_BRAKE_COAST);

	while(getTrayPos() > 50) { //runs the tray forward until it is vertical
		runTray(calcTrayPow(1));
		delay(10);
	}
	delay(100);
	runTray(0);

	if(intkSpeed) //if requested, the intake will run outwards
		runIntk(-intkSpeed);
	moveStraight(-15, 1000); //moves back
	runIntk(0);

	leftIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD); //allows the intake to hold the cubes again
	rightIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);

}

enum class trayStatus;
trayStatus trayStat = trayStatus::idle;

void ctrlTray(void* param) { //tray control task

	while(true) {

		if(trayStat == trayStatus::idle) { //doesnt make the tray hold the position, lets the motor rest
			tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
			runTray(0);
		}

		else if(trayStat == trayStatus::hold) { //holds the tray in place
			tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
			runTray(0);
		}

		else if(trayStat == trayStatus::outtake) { //runs the tray out until it is vertical
			if(getTrayPos() > 20)
				runTray(calcTrayPow(1));
			else 
				trayStat = trayStatus::hold; //then holds the tray's position
		}

		else if(trayStat == trayStatus::retract) { //runs the tray in until it is at the rest position
			if(getTrayPos() < 1000)
				runTray(calcTrayPow(0));
			else 
				trayStat = trayStatus::idle; //then lets the tray motor rest
		}

		delay(50);

	}

}