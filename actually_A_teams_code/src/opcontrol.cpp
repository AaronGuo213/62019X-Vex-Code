#include "main.h"
void opcontrol() {

	std::uint_least32_t now = millis();
	tray.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    intk1.set_brake_mode(E_MOTOR_BRAKE_HOLD);
    intk2.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	arms.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	/*PID arm = initPID(1, 0, 0, 0.7, 0, 0);
	int armSetPoint = 0;
	double armVal = 0;*/

	while(true) {

		runLeftBase(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
		runRightBase(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

		if(master.get_digital(E_CONTROLLER_DIGITAL_R1))
			runIntk(100);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R2))
			runIntk(-100);
		else
			runIntk(0);

		if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
			runTray(getTrayPow());
			//armSetPoint = 0;
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
			runTray(-100);
			//armSetPoint = 0;
		}
		else
			runTray(0);

		/*if(master.get_digital(E_CONTROLLER_DIGITAL_UP))
			armSetPoint = 850;
		else if(master.get_digital(E_CONTROLLER_DIGITAL_LEFT))
			armSetPoint = 650;
		else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			armSetPoint = 0;

		arm.error = armSetPoint - arms.get_position();
		armVal = runPID(&arm);
		if(armSetPoint != 0) {
			if(tray.get_position() < 500) {
				runTray(100);
				arms.move_voltage(0);
			}
			else {
				runTray(0);
				arms.move_voltage(armVal * 120);
			}
		}
		else
			arms.move_voltage(armVal * 120);*/

		if(master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
			if(tray.get_position() < 500)
				runTray(100);
			else {
				arms.move_voltage(12000);
				runTray(0);
			}
		}

		else if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
			arms.move_voltage(-12000);
		}

		else 
			arms.move_voltage(0);

		std::cout << "trayPos: " << tray.get_position() << " | armPos: " << arms.get_position() << std::endl;

		delay(10);

	}

}