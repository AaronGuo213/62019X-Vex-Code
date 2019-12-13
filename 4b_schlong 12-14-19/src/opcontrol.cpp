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

		/*if(l1()) {
			while(!l2() && !r2()) {
				runLeftBase(60);
				runRightBase(60);
				runIntk(100);
			}
		}

		if(r1()) {
			while(!l2() && !r2()) {
				runLeftBase(70);
				runRightBase(70);
				runIntk(100);
			}
		}

		runIntk(0);*/

		//std::cout << tray.get_position() << std::endl;
		//std::cout << getLeftEnc() << " | " << getRightEnc() << std::endl;
		//std::cout << getLiftHeight() << std::endl;
		std::cout << leftIntk.get_position() << std::endl;;
		
		Task::delay_until(&now, 10);

	}

}