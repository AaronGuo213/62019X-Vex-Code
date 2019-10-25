#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();

	float leftVal, rightVal;

	while(true) {

		updateBase();
		updateLift();
		updateIntk();
		
		Task::delay_until(&now, 10);

	}

}