#include "main.h"
void opcontrol() {

	std::uint_least32_t now = millis();
	//tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    intk1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    intk2.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	arms.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	bool mode = false;
	double intkVal;

	while(true) {

		runLeftBase(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
		runRightBase(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1))
			intkVal = 100;
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
			intkVal = -100;
		else
			intkVal = 0;

		if(!mode) {
			if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
				runTray(getTrayPow(1));
			else if(master.get_digital(E_CONTROLLER_DIGITAL_L2))
				runTray(getTrayPow(0));
			else
				runTray(0);
		}

		else {
			if(master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
				if(arms.get_position() < 250)
					intkVal = -100;
				runArms(100);
			}
			else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
				runArms(-100);
			}
			else {
				runArms(0);
			}
		}

		runIntk(intkVal);

		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
			mode = !mode;
			master.rumble(".");
		}

		/*if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
			runTray(getTrayPow(1));
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2))
			runTray(getTrayPow(0));
		else
			runTray(0);

		if(master.get_digital(E_CONTROLLER_DIGITAL_UP))
			runArms(100);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			runArms(-100);
		else 
			runArms(0);*/

		std::cout << "trayPos: " << tray.get_position() << " | armPos: " << arms.get_position() << std::endl;

		delay(10);

	}

}