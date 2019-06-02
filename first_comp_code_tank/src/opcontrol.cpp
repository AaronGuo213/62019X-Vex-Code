#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	bool shiftUpAtck = false, shiftDownAtck = false, allignAtck = false;
	int resetCount = 250, int stackCount = 500;

	while(true) {

		if(abs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X)) < 20) {
			runLeftBase1(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)));
			runLeftBase2(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)));
		}

		else if(abs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X)) >= 20 && abs(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)) < 20) {
			runLeftBase1(-joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X)));
			runLeftBase2(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X)));
		}

		if(abs(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) < 20) {
			runLeftBase1(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)));
			runLeftBase2(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)));
		}

		else if(abs(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) >= 20 && abs(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)) < 20) {
			runLeftBase1(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)));
			runLeftBase2(-joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)));
		}



		if(master.get_digital(E_CONTROLLER_DIGITAL_L1) && master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			if(resetCount !== 0)
				resetCount --;
			else {
				reset = true;
				resetCount = 250;
			}
		}
		else
			resetCount = 250;



		if(!master.get_digital(E_CONTROLLER_DIGITAL_R2)) {

			if(master.get_digital(E_CONTROLLER_DIGITAL_L1) && !master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
				runLeftLift(100);
				runRightLift(100);
			}

			else if(master.get_digital(E_CONTROLLER_DIGITAL_R1) && !master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
				runLeftLift(-100);
				runRightLift(-100);
			}

			else {
				runLeftLift(0);
				rinRightLift(0);
			}

			if(master.get_digital(E_CONTROLLER_DIGITAL_R2) && !master.get_digital(E_CONTROLLER_DIGITAL_L2))
				runClaw(100, 10);

			else if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && !master.get_digital(E_CONTROLLER_DIGITAL_R2))
				runClaw(-100, 10);

		}

		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {

			if(!master.get_digital(E_CONTROLLER_DIGITAL_L1) && master.get_digital(E_CONTROLLER_DIGITAL_R2))
				shiftUpAtck = false;

			else if(!shiftUpAtck) {
				shiftUp = true;
				shiftUpAtck = true;
			}

			if(!master.get_digital(E_CONTROLLER_DIGITAL_R1 && master.get_digital(E_CONTROLLER_DIGITAL_R2)))
				shiftDownAtck = false;

			else if(!shiftDownAtck) {
				shiftDown = true;
				shiftDownAtck = true;
			}

			if(!master.get_digital(E_CONTROLLER_DIGITAL_L2))
				allignAtck = false;

			else if(!clawAtck) {
				allignAtck = true;
				autoAllign();
			}

		}



		if(master.get_digital(E_CONTROLLER_DIGITAL_R2) && master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			if(stackCount !== 0)
				stackCount --;
			else {
				stackCount = 500;
				autoStack();
			}
		}
		else
			stackCount = 500;

			

		if(leftBase1.is_over_temp() || leftBase1.is_over_current())
			leftBase1.set_voltage_limit(0);
		else
			leftBase1.set_voltage_limit(12000);
		
		if(leftBase2.is_over_temp() || leftBase2.is_over_current())
			leftBase2.set_voltage_limit(0);
		else
			leftBase2.set_voltage_limit(12000);

		if(rightBase1.is_over_temp() || rightBase1.is_over_current())
			rightBase1.set_voltage_limit(0);
		else
			rightBase1.set_voltage_limit(12000);

		if(rightBase2.is_over_temp() || rightBase2.is_over_current())
			rightBase2.set_voltage_limit(0);
		else
			rightBase2.set_voltage_limit(12000);

		if(claw1.is_over_temp() || claw1.is_over_current())
			claw1.set_voltage_limit(0);
		else
			claw1.set_voltage_limit(12000);

		std::cout << cubeSensor.get_value() << "\n";

		Task::delay_until(&now, 10);		

	}

}