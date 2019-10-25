#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();

	float leftVal, rightVal;

	while(true) {

		/*leftVal = lY();
		rightVal = rX();
		if(rightVal > 3) {
			runLeftBase(leftVal);
			runRightBase(leftVal - 2 * rightVal);
		}

		else if(rightVal < -3) {
			runLeftBase(leftVal + 2 * rightVal);
			runRightBase(leftVal);
		}

		else {
			runLeftBase(0);
			runRightBase(0);
		}*/
		std::cout << getLiftHeight() << std::endl;
		

		updateBase();
		updateLift();
		updateIntk();
		
		Task::delay_until(&now, 10);

	}

}