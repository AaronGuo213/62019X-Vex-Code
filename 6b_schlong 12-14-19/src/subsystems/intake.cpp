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

	intkSafetyNet();

}

void intkSafetyNet() {

	if(leftIntk.is_over_temp())
		leftIntk.set_voltage_limit(0);
	else
		leftIntk.set_voltage_limit(12000);

	if(rightIntk.is_over_temp())
		rightIntk.set_voltage_limit(0);
	else
		rightIntk.set_voltage_limit(12000);

}

void runTray(double percent) {

    tray.move_voltage(percent * 120);
	
}

int getTrayPos() {

	return tray.get_position();
		
}

 //calculates the power to send to the tray motor for a consistent outtaking process
double calcTrayPow(bool moveForward) {

	if(moveForward && getTrayPos() < 950)
		return(950 - getTrayPos()) / 8 + 15;
		//return (1130 - getTrayPos()) / 5 + 5;

	if(!moveForward && getTrayPos() > 0)
		return -getTrayPos();

	return 0;

}

void updateTray() {

	/*if(r2() && !l2()) { //r1 pressed runs the tray outward
		runTray(calcTrayPow(1));
		//runTray(100);
	}

	else if(l2() && !r2()) { //r2 pressed runs the tray inward
		runTray(calcTrayPow(0));
	}

	else //otherwise dont run the tray motor
		runTray(0);*/

	if(r2() && !l2()) { //r1 pressed runs the tray outward
		trayStat = trayStatus::manual;
		runTray(calcTrayPow(1));
	}

	else if(l2() && !r2()) { //r2 pressed runs the tray inward
		trayStat = trayStatus::manual;
		runTray(calcTrayPow(0));
	}

	else if(getTrayPos() < 200) {
		trayStat = trayStatus::idle;
	}

	else if(trayStat == trayStatus::manual) { //otherwise dont run the tray motor
		traySetPoint = getTrayPos();
		trayStat = trayStatus::hold;
	}

	traySafetyNet();

}

void traySafetyNet() {

	if(tray.is_over_temp())
		tray.set_voltage_limit(0);
	else 
		tray.set_voltage_limit(12000);

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

double traySetPoint = 0;
bool resetTrayIntegral = false;
enum class trayStatus;
trayStatus trayStat = trayStatus::idle;

void ctrlTray(void* param) { //tray control task

	std::uint32_t now = millis();
	PID hold = initPID(1, 0, 0, 1, 0, 0); //kP = 0.3, kI = 0.0001
	PID move = initPID(1, 0, 0, 1, 0, 0); //kP = 0.3, kI = 0.0001
	double holdVal, moveVal;

	while(true) {

		traySetPoint = traySetPoint > 950 ? 950 : traySetPoint; //lift cannot be higher than 1800
        traySetPoint = traySetPoint < 0 ? 0 : traySetPoint; //lift cannot be lower than 0

		if(resetTrayIntegral) {
            hold.integral = 0;
            move.integral = 0;
            resetIntegral = false;
        }

		if(trayStat != trayStatus::manual) {

			if(trayStat == trayStatus::idle) { //doesnt make the tray hold the position, lets the motor rest
				runTray(0);
			}

			else if(trayStat == trayStatus::hold) { //holds the tray in place
				hold.error = (traySetPoint - getTrayPos()); //updates error for holdPID
                holdVal = runPID(&hold); //updates the holdVal, reference misc.cpp
                runTray(holdVal);
				//std::cout << "traySetPoint: " << traySetPoint << " | trayPos: " << getTrayPos() << " | hold.error: " << hold.error << " | holdVal: " << holdVal << std::endl;
			}

		}

		traySafetyNet();
		Task::delay_until(&now, 50);

	}

}