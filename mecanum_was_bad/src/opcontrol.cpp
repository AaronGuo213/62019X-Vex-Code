#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	resetBaseEnc();
	bool outtake = false, lever = false;

	while(true) {

		runLeftBase(joyValRemap(lY()));
		runRightBase(joyValRemap(rY()));


		if(l1() && !r1() && !r2()) {
			ctrlLift = false;
			runLeftLift(100);
			runRightLift(100);
			lever = true;
		}
		else if(r1() && !l1() && !r2()) {
			ctrlLift = false;
			runLeftLift(-80);
			runRightLift(-80);
			lever = true;
		}
		else if(lever){
			slowHold = true;
			lever = false;
		}


		if(l2() && !r2()) {
			runClaw(100, 2);
		}

		if(!l2() && r2()) {
			runClaw(-100, 2);
			ctrlLift = false;
			outtake = true;
		}
		else if(outtake) {
			liftSetPoint = getLiftHeight();
			ctrlLift = true;
			outtake = false;
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

		//std::cout << getLeftEnc() << " | " << getRightEnc() << " | " << getYawEnc() << std::endl;
		//std::cout << getLeftLiftHeight() << " | " << getRightLiftHeight() << " | " << getLiftHeight() << std::endl;
		std::cout << liftSetPoint << std::endl;
		Task::delay_until(&now, 1);		

	}

}