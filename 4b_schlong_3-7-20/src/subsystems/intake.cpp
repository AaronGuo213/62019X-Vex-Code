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
		coastIntk();
		runIntk(100);
	}

	else if((!l1Pressed() && r1Pressed()) || (!l1Pressed(partner) && r1Pressed(partner))) { //r1 pressed runs intake outwards
		brakeIntk();
		if(!isSkills)
			runIntk(-100);
		else
			runIntk(-60); //skills
	}

	else { //otherwise dont run the intake
		brakeIntk();
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

void queueIntk(void* param) {

	intkQueue* theQueue = (intkQueue*)param;
	double power = theQueue->percent;
	int time = theQueue->time;
	for(int i = 0; i < time; i+=10) {
		runIntk(power);
		delay(10);
	}
	runIntk(0);

}

void runIntk(double percent, int time) {

	//runs the intake for a certain time before stopping
	intkQueue newQueue = {percent, time};
	Task runIntkTimed(queueIntk, &newQueue, TASK_PRIORITY_MIN, TASK_STACK_DEPTH_MIN, "timed running intk task");
	delay(20);

}