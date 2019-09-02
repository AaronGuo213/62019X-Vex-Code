#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();

	float r, theta, leftTransVal, rightTransVal, turnVal;
	bool shiftUpAtck = true, shiftDownAtck = true, resetAtck = true, resetLift = false;

	while(true) {

		//std::cout << getBaseMotorEnc() << "\n";

		r = pow(pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 2) + pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 2), 0.5) > 127 ? 127 : pow(pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 2) + pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 2), 0.5); //finds the absolute value of the joystick regardless of angle
		r = joyValRemap(r); //remaps the joystick value to a more optimized array of values
		theta = findTheta(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
		
		leftTransVal = 0.75 * leftBaseRemap(r, theta); //uses trigonometry to find the value the left motors should run at
		rightTransVal = 0.75 * rightBaseRemap(r, theta); //uses trigonometry to find the value the right motors should run at
		turnVal = joyValRemap(master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)); //uses the right joystick's value to turn
		turnVal *= 3 / 4; //limits the voltage for turning to 75% of max voltage

		runLeftBase1(leftTransVal + turnVal);
		runLeftBase2(leftTransVal - turnVal);
		runRightBase1(rightTransVal + turnVal);
		runRightBase2(rightTransVal - turnVal);



		if(master.get_digital(E_CONTROLLER_DIGITAL_L1) && !master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
			manual = true;
			runLift(100);
		}
		else if(master.get_digital(E_CONTROLLER_DIGITAL_R1) && !master.get_digital(E_CONTROLLER_DIGITAL_L1) && !liftLimit.get_value()) {
			manual = true;
			runLift(-100);
		}
		else { //if R1 and L1 are both pressed or not pressed
			manual = false;
			runLift(0);
		}

		if(!master.get_digital(E_CONTROLLER_DIGITAL_UP)) //switch to allow holding the button to toggle once
			resetAtck = false;
		else if(!resetAtck) {
			reset = true;
			resetAtck = true;
		}

		if(reset && !liftLimit.get_value()) //if reset is desired, the lift will move down until the button is triggered
			runLift(-100);
		else if(reset && liftLimit.get_value()) {
			runLift(0);
			reset = false;
		}

		/*if(!master.get_digital(E_CONTROLLER_DIGITAL_L1))
			shiftUpAtck = false;
		else if(!shiftUpAtck) {
			shiftUp = true;
			shiftUpAtck = true;
		}

		if(!master.get_digital(E_CONTROLLER_DIGITAL_R1))
			shiftDownAtck = false;
		else if(!shiftDownAtck) {
			shiftDown = true;
			shiftDownAtck = true;
		}*/



		if(master.get_digital(E_CONTROLLER_DIGITAL_R2) && !master.get_digital(E_CONTROLLER_DIGITAL_L2))
			runClaw(100);
		else if(master.get_digital(E_CONTROLLER_DIGITAL_L2) && !master.get_digital(E_CONTROLLER_DIGITAL_R2))
			runClaw(-100);
		else
			runClaw(0);



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

		if(claw1.is_over_temp() || claw1.is_over_current())
			claw1.set_voltage_limit(0);
		else
			claw1.set_voltage_limit(12000);

		std::cout << liftLimit.get_value() << "\n";

		Task::delay_until(&now, 10);		

	}

}