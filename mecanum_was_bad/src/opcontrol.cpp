#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	resetBaseEnc();

	while(true) {

		runLeftBase(joyValRemap(lY()));
		runRightBase(joyValRemap(rY()));


		if(l1() && !r1() && !r2()) {
			runLeftLift(100);
			runRightLift(100);
			//liftSetPoint += 5;
		}
		else if(r1() && !l1() && !r2()) {
			runLeftLift(-100);
			runRightLift(-100);
			//liftSetPoint -= 5;
		}
		else {
			runLeftLift(0);
			runRightLift(0);
		}


		if(l2() && !r2()) {
			runClaw1(70);
			runClaw2(70);
		}
		else if(!l2() && r2()) {
			runClaw1(-70);
			runClaw2(-70);
		}
		else {
			runClaw1(0);
			runClaw2(0);
		}
			

		if(leftBase1.is_over_temp() || leftBase1.is_over_current())
			leftBase1.set_voltage_limit(0);
		else
			leftBase1.set_voltage_limit(12000);
		
		if(leftBase2.is_over_temp() || leftBase2.is_over_current())
			leftBase2.set_voltage_limit(0);
		else
			leftBase2.set_voltage_limit(12000);

		if(rightBase1.is_over_temp() || rightBase1.is_over_current())
			rightBase1.set_voltage_limit(0);
		else
			rightBase1.set_voltage_limit(12000);

		if(rightBase2.is_over_temp() || rightBase2.is_over_current())
			rightBase2.set_voltage_limit(0);
		else
			rightBase2.set_voltage_limit(12000);

		//std::cout << leftBase1.get_position() << " | " << leftBase2.get_position() << " || " << rightBase1.get_position() << " | " << rightBase2.get_position() << std::endl;

		Task::delay_until(&now, 1);		

	}

}