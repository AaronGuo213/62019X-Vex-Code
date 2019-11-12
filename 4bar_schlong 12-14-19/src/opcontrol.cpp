#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();
	resetBaseEnc();
	resetYawEnc();
	Task trackingGo(trackPos, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

	while(true) {

		updateBase();
		updateLift();
		updateIntk();

		std::cout << getLeftEnc() << " | " << getRightEnc() << std::endl;
		//std::cout << getLiftHeight() << std::endl;
		
		Task::delay_until(&now, 10);

	}

}