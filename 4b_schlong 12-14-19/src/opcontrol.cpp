#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();
	//liftStat = LiftStatus::holdDown;
	resetBaseEnc();
	resetYawEnc();
	//Task trackingGo(trackPos, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

	while(true) {

		updateBase();
		updateLift();
		updateIntk();
		updateTray();

		//std::cout << tray.get_position() << std::endl;
		//std::cout << getLeftEnc() << " | " << getRightEnc() << std::endl;
		std::cout << getLiftHeight() << std::endl;
		
		Task::delay_until(&now, 10);

	}

}