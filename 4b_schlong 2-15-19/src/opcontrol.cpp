#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();
	resetBaseEnc();
	Odometry* tracker = new Odometry(0, 0, 0);
	Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

	while(true) {

		//update functions
		updateBase();
		updateLift();
		updateIntk();
		updateTray();

		/*if(master.get_digital(E_CONTROLLER_DIGITAL_A))
			turnToAngle(tracker, 0);
		std::cout << tracker->getAngle() << std::endl;*/
		//std::cout << tracker->getAngle() << " | " << tracker->getX() << " | " << tracker->getY() << std::endl;

		//std::cout << getLeftEnc() << " | " << getRightEnc() << std::endl;
		//std::cout << getTrayPos() << std::endl;
		Task::delay_until(&now, 10);

	}

}