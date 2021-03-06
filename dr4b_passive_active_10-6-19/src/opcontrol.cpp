#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();
	resetPID = true;
	bool intkPos = true, //determines the position of the intake pistons, flips when intake is toggled
		intkAtck = false, //used to limit the holding of a button to a single toggle
		lockAtck = false,
		stackAtck = false;

	while(true) {

		runLeftBase(joyValRemap(lY()));
		runRightBase(joyValRemap(rY()));


		if(l1() && !r1()) { //to move the lift up
			holdLift = false; //stops holding the lift in place
			slowLift = false;
			stack = false;
			runLeftLift(100); //runs the lift motors at 100% up
			runRightLift(100);
		}

		else if(r1() && !l1()) { //to move the lift down
			holdLift = false; //stops holding the lift in place
			slowLift = false;
			stack = false;
			runLeftLift(-100); //runs the lift motors at 100% down
			runRightLift(-100);
		}

		else if(!slowLift && !holdLift) { //to hold the lift in place
			slowTimer = 300; //sets the max timer for the slowLift phase
			slowLift = true; //activates the deceleration of the lift
		}


		if(!r2())
			stackAtck = true;
		
		else if(stackAtck) { //allows the button to be held down and intake toggles once
			stackAtck = false;
			stack = true;
		}


		if(!l2())
			intkAtck = true;

		else if(intkAtck) { //allows the button to be held down and intake toggles once
			intkAtck = false;
			setIntk(intkPos);
			intkPos = !intkPos;
		}

		if(master.get_digital(E_CONTROLLER_DIGITAL_A))
			setLock(0);

		else
			setLock(!intkPos);

		if(master.get_digital(E_CONTROLLER_DIGITAL_DOWN))
			resetPID = true;
			

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
		
		Task::delay_until(&now, 10);		

	}

}