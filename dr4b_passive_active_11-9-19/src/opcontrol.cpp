#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();

	while(true) {

		updateBase();
		updateLift();
		updateIntk();

		std::cout << getLiftHeight() << std::endl;
		
		Task::delay_until(&now, 10);

	}

}