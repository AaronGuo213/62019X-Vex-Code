#include "main.h"

void runIntk(double percent) {

    leftIntk.move_voltage(percent * 120); //runs intake motors out of 12000mV
	rightIntk.move_voltage(percent * 120);

}

void updateIntk() {

    if(l1() && !r1()) //l1 pressed runs intake inwards
		runIntk(100);

	else if(r1() && !l1()) //r1 pressed runs intake outwards
		runIntk(-100);

	else //otherwise dont run the intake
		runIntk(0);

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