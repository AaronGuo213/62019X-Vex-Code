#include "main.h"
void opcontrol() {

	std::uint_least32_t now = millis();
	//tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    intk1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    intk2.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	arms.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	bool mode = false;

	while(true) {

		runLeftBase(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
		runRightBase(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1))
			runIntk(100);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
			runIntk(-100);
		else
			runIntk(0);

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
				if(tray.get_position() < 800) {
					runTray(100);
					runArms(0);
				}
				else {
					runArms(100);
					runTray(0);
				}
			}
			else if(master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
				if(arms.get_position() > 50) {
					runArms(-100);
					runTray(0);
				}
				else if(tray.get_position() > 0) {
					runArms(0);
					runTray(-100);
				}
				else {
					runTray(0);
				}
			}
			else {
				runArms(0);
				runTray(0);
			}
		}

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