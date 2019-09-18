#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = liftPot.get_value();
	bool intkPos = false, //determines the position of the intake pistons, flips when intake is toggled
		intkAtck = false; //used to limit the holding of a button to a single toggle

	while(true) {

		runLeftBase(joyValRemap(lY()));
		runRightBase(joyValRemap(rY()));


		if(l1() && !r1()) {
			//holdLift = false;
			//slowLift = false;
			runLeftLift(100);
			runRightLift(100);
		}

		else if(r1() && !l1()) {
			//holdLift = false;
			//slowLift = false;
			runLeftLift(-100);
			runRightLift(-100);
		}

		//else if(!slowLift && !holdLift)
			//slowLift = true;

		else { //stop all lift movement when both l1 and r1 are pressed or released
			runLeftLift(0);
			runRightLift(0);
		}


		if(l2())
			intkAtck = false;

		else if(!intkAtck) { //allows the button to be held down and intake toggles once
			intkAtck = true;
			setIntk(intkPos);
			intkPos = !intkPos;
		}
			

		if(leftBase1.is_over_temp() || leftBase1.is_over_current())
			leftBase1.set_voltage_limit(0);
		else
			leftBase1.set_voltage_limit(12000);

		if(rightBase1.is_over_temp() || rightBase1.is_over_current())
			rightBase1.set_voltage_limit(0);
		else
			rightBase1.set_voltage_limit(12000);

		if(leftBase2.is_over_temp() || leftBase2.is_over_current())
			leftBase2.set_voltage_limit(0);
		else
			leftBase2.set_voltage_limit(12000);

		if(rightBase2.is_over_temp() || rightBase2.is_over_current())
			rightBase2.set_voltage_limit(0);
		else
			rightBase2.set_voltage_limit(12000);

		//std::cout << liftPot.get_value() << std::endl;

		Task::delay_until(&now, 1);		

	}

}