#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	bool shiftUpAtck = false, shiftDownAtck = false, allignAtck = false, clawAtck = false;
	int clawPos = 1;
	int stackCount = 500;
	resetBaseEnc();

	while(true) {

		if(abs(lX()) < 20 && abs(rX()) < 20) {
			runLeftBase1(joyValRemap(lY()));
			runLeftBase2(joyValRemap(lY()));
			runRightBase1(joyValRemap(rY()));
			runRightBase2(joyValRemap(rY()));
		}

		else if(abs(lX()) >= 20 && abs(lY()) < 20) {
			leftBase1.move_velocity(joyValRemap(lX()) * 2);
			leftBase2.move_velocity(-joyValRemap(lX()) * 2);
			rightBase1.move_velocity(-joyValRemap(lX()) * 2);
			rightBase2.move_velocity(joyValRemap(lX()) * 2);
		}

		else if(abs(rX()) >= 20 && abs(rY() < 20)) {
			leftBase1.move_velocity(joyValRemap(rX()) * 2);
			leftBase2.move_velocity(-joyValRemap(rX()) * 2);
			rightBase1.move_velocity(-joyValRemap(rX()) * 2);
			rightBase2.move_velocity(joyValRemap(rX()) * 2);
		}


		if(l1() && !r1() && !r2()) {
			runLeftLift(100);
			runRightLift(100);
		}

		else if(r1() && !l1() && !r2()) {
			runLeftLift(-100);
			runRightLift(-100);
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
				//autoStack();
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

		std::cout << leftBase1.get_position() << " | " << leftBase2.get_position() << " || " << rightBase1.get_position() << " | " << rightBase2.get_position() << std::endl;

		Task::delay_until(&now, 1);		

	}

}