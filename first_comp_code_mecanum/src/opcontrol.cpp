#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	bool shiftUpAtck = false, shiftDownAtck = false, allignAtck = false, clawAtck = false, clawPos = true;
	int stackCount = 500;

	while(true) {

		if(abs(lX()) < 20 && abs(rX()) < 20) {
			runLeftBase1(joyValRemap(lY()));
			runLeftBase2(joyValRemap(lY()));
			runRightBase1(joyValRemap(rY()));
			runRightBase2(joyValRemap(rY()));
		}

		else if(abs(lX())) >= 20 && abs(lY()) < 20) {
			runLeftBase1(joyValRemap(lX()));
			runLeftBase2(-joyValRemap(lX()));
			runRightBase1(-joyValRemap(lX()));
			runRightBase2(joyValRemap(lX()));
		}

		else if(abs(rX()) >= 20 && abs(rY() < 20) {
			runLeftBase1(joyValRemap(rX()));
			runLeftBase2(-joyValRemap(rX()));
			runRightBase1(-joyValRemap(rX()));
			runRightBase2(joyValRemap(rX()));
		}


		if(l1() && !r1() && !r2()) {
			runLeftLift(80);
			runRightLift(80);
		}

		else if(r1() && !l1() && !r2()) {
			runLeftLift(-80);
			runRightLift(-80);
		}

		else {
			runLeftLift(0);
			runRightLift(0);
		}


		if(!(l2() && !r2()))
			clawAtck = false;
		
		else if(!clawAtck) {
			clawPos = !clawPos;
			claw.set_value(clawPos);
			clawAtck = true;
		}


		if(!(l1() && r2()))
			shiftUpAtck = false;

		else if(!shiftUpAtck) {
			shiftUp = true;
			shiftUpAtck = true;
		}


		if(!(r1() && r2()))
			shiftDownAtck = false;

		else if(!shiftDownAtck) {
			shiftDown = true;
			shiftDownAtck = true;
		}


		if(!(l2() && r2()))
			allignAtck = false;

		else if(!allignAtck) {
			allignAtck = true;
			autoAllign();
		}


		if(r2() && l2()) {
			if(stackCount != 0)
				stackCount --;
			else {
				stackCount = 500;
				autoStack();
			}
		}
		else
			stackCount = 500;
			

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

		//std::cout << cubeSensor.get_value() << "\n";

		Task::delay_until(&now, 1);		

	}

}