#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();

	float r, theta, leftTransVal, rightTransVal, turnVal;
	bool shiftUpAtck = 1, shiftDownAtck = 1;

	while(true) {

		r = pow(pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 2) + pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 2), 0.5) > 127 ? 127 : pow(pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 2) + pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 2), 0.5);
		r = joyValRemap(r);
		theta = findTheta(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
		
		leftTransVal = leftBaseRemap(r, theta);
		rightTransVal = rightBaseRemap(r, theta);
		turnVal = joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X));
		turnVal = r > 0 ? turnVal * 3 / 4 : turnVal;

		runLeftBase1(leftTransVal + turnVal);
		runLeftBase2(leftTransVal - turnVal);
		runRightBase1(rightTransVal + turnVal);
		runRightBase2(rightTransVal - turnVal);


		if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && !master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
			manual = true;
			runLift(100);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L1) && !master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			manual = true;
			runLift(-100);
		}
		else {
			manual = false;
			runLift(0);
		}


		if(!master.get_digital(E_CONTROLLER_DIGITAL_UP))
			shiftUpAtck = 0;
		else if(!shiftUpAtck) {
			shiftUp = true;
			shiftUpAtck = 1;
		}

		if(!master.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			shiftDownAtck = 0;
		else if(!shiftDownAtck) {
			shiftDown = true;
			shiftDownAtck = 1;
		}


		if(master.get_digital(E_CONTROLLER_DIGITAL_R1) && !master.get_digital(E_CONTROLLER_DIGITAL_R2))
			runClaw(100);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2) && !master.get_digital(E_CONTROLLER_DIGITAL_R1))
			runClaw(-100);
		else
			runClaw(0);

		


		if(leftBase1.is_over_temp() || leftBase1.is_over_current())
			leftBase1.set_voltage_limit(0);
		else
			leftBase1.set_voltage_limit(12000);
		
		if(leftBase2.is_over_temp() || leftBase2.is_over_current())
			leftBase2.set_voltage_limit(0);
		else
			leftBase1.set_voltage_limit(12000);

		if(rightBase1.is_over_temp() || rightBase1.is_over_current())
			rightBase1.set_voltage_limit(0);
		else
			rightBase1.set_voltage_limit(12000);

		if(rightBase2.is_over_temp() || rightBase2.is_over_current())
			rightBase2.set_voltage_limit(0);
		else
			rightBase2.set_voltage_limit(12000);

		if(lift1.is_over_temp() || lift1.is_over_current())
			lift1.set_voltage_limit(0);
		else
			lift1.set_voltage_limit(12000);

		if(claw.is_over_temp() || claw.is_over_current())
			claw.set_voltage_limit(0);
		else
			claw.set_voltage_limit(12000);

		Task::delay_until(&now, 10);		

	}

}