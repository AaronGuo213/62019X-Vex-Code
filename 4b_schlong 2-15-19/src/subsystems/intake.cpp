#include "main.h"

void runIntk(double percent) {

    leftIntk.move_voltage(percent * 120); //runs intake motors out of 12000mV
	rightIntk.move_voltage(percent * 120);

}

void runIntkDist(double dist, double velocity) {

	leftIntk.move_relative(dist, velocity); //runs the intake a certain distance
	rightIntk.move_relative(dist, velocity);

}

void updateIntk() {

    if((l1Pressed() && !r1Pressed()) || (l1Pressed(partner) && !r1Pressed(partner))) { //l1 pressed runs intake inwards
		//coastIntk();
		runIntk(100);
	}

	else if((!l1Pressed() && r1Pressed()) || (!l1Pressed(partner) && r1Pressed(partner))) { //r1 pressed runs intake outwards
		//coastIntk();
		runIntk(-100);
	}

	else { //otherwise dont run the intake
		//brakeIntk();
		runIntk(0);
	}

	//check for overheating of the intake motors
	intkSafetyNet();

}

void intkSafetyNet() {

	//checks the temperature of the intake motors
	if(leftIntk.is_over_temp())
		leftIntk.set_voltage_limit(0);
	else
		leftIntk.set_voltage_limit(12000);

	if(rightIntk.is_over_temp())
		rightIntk.set_voltage_limit(0);
	else
		rightIntk.set_voltage_limit(12000);

}

void brakeIntk() {

	leftIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	rightIntk.set_brake_mode(E_MOTOR_BRAKE_HOLD);

}

void coastIntk() {

	leftIntk.set_brake_mode(E_MOTOR_BRAKE_COAST);
	rightIntk.set_brake_mode(E_MOTOR_BRAKE_COAST);

}

int intkTimer = 0;
double intkPow = 0;

void ctrlIntk(void *param) {
	//intake control task used for running the intake with a timer

	std::uint32_t now = millis();
	bool stopIntk = false;
	while(true) {
		//updates every 50ms

		//updates the timer for the intake
		if(intkTimer) {
			runIntk(intkPow);
			intkTimer -= 50;
			stopIntk = true;
		}

		//if the timer runs out, stop the intake
		else if(stopIntk) {
			stopIntk = false;
			runIntk(0);
		}

		Task::delay_until(&now, 50);

	}

}

void runIntk(double percent, int time) {

	//updates the intake control task
	intkPow = percent;
	intkTimer = time;

}