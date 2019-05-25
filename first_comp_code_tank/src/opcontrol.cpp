#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	bool shiftUpAtck = true, shiftDownAtck = true;

	while(true) {

		runLeftBase(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)));
		runRightBase(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)));

		if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN) && !master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
			manual = true;
			runLift(-100);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_UP) && !master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
			manual = true;
			runLift(100);
		}
		else {
			manual = false;
			runLift(0);
		}

		if(!master.get_digital(E_CONTROLLER_DIGITAL_L1))
			shiftUpAtck = false;
		else if(!shiftUpAtck) {
			shiftUp = true;
			shiftUpAtck = true;
		}

		if(!master.get_digital(E_CONTROLLER_DIGITAL_R1))
			shiftDownAtck = false;
		else if(!shiftDownAtck) {
			shiftDown = true;
			shiftDownAtck = true;
		}



		if(master.get_digital(E_CONTROLLER_DIGITAL_R2) && !master.get_digital(E_CONTROLLER_DIGITAL_L2))
			runClaw(100, 1);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && !master.get_digital(E_CONTROLLER_DIGITAL_R2))
			runClaw(-100, 1);
			


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