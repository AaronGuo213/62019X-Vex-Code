#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();

	while(true) {

		runLeftBase(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)));
		runRightBase(joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)));


		if(master.get_digital(E_CONTROLLER_DIGITAL_L1) && !master.get_digital(E_CONTROLLER_DIGITAL_L2))
			runIntk(100);

		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && !master.get_digital(E_CONTROLLER_DIGITAL_L1))
			runIntk(-100);

		else
			runIntk(0);


		if(master.get_digital(E_CONTROLLER_DIGITAL_R1) && !master.get_digital(E_CONTROLLER_DIGITAL_R2))
			runTray(100);

		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2) && !master.get_digital(E_CONTROLLER_DIGITAL_R1))
			runTray(-100);

		else
			runTray(0);


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

		if(intk1.is_over_temp() || intk1.is_over_current())
			intk1.set_voltage_limit(0);
		else
			intk1.set_voltage_limit(12000);

		if(intk2.is_over_temp() || intk2.is_over_current())
			intk2.set_voltage_limit(0);
		else
			intk2.set_voltage_limit(12000);

		if(tray.is_over_temp() || tray.is_over_current())
			tray.set_voltage_limit(0);
		else
			tray.set_voltage_limit(12000);

		Task::delay_until(&now, 10);		

	}

}