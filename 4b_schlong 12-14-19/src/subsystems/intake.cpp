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

int intkTimer = 0;
double intkPow = 0;

void ctrlIntk(void *param) {

	std::uint32_t now = millis();
	while(true) {

		if(intkTimer) {
			runIntk(intkPow);
			intkTimer -= 50;
		}

		Task::delay_until(&now, 50);

	}

}

void runIntk(double percent, int time) {

	intkPow = percent;
	intkTimer = time;

}