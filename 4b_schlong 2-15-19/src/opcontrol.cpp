#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();
	resetBaseEnc();
	//Task trackingGo(trackPos, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

	while(true) {

		//update functions
		updateBase();
		updateLift();
		updateIntk();
		updateTray();
		
		Task::delay_until(&now, 10);

	}

}