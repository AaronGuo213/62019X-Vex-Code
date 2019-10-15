#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();
	bool x = false, b = false, up = false, down = false;
	int power = 0;

	while(true) {

		updateBase();
		updateLift();
		updateIntk();

		if(l1()&& !r1())
			runLift(100);

		else if(!l1()&& r1())
			runLift(-100);

		else
			runLift(0);

		if(master.get_digital(E_CONTROLLER_DIGITAL_X))
			x = true;
		else if(x) {
			x = false;
			power ++;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_B))
			b = true;
		else if(x) {
			b = false;
			power --;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_UP))
			up = true;
		else if(x) {
			up = false;
			power += 10;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			down = true;
		else if(x) {
			down = false;
			power -= 10;
		}

		if(!master.get_digital(E_CONTROLLER_DIGITAL_A))
			runLift(power);
		else 
			runLift(0);
		std::cout << power << std::endl;
		
		Task::delay_until(&now, 10);

	}

}