#include "main.h"

void setIntk(bool status) {

    intk.set_value(status);
    lock.set_value(status);

}

void setLock(bool status) {

    lock.set_value(status);

}

bool intkSwitch = false, intkPos = true;

void updateIntk() {

    if(!l2())
		intkSwitch = true;
	else if(intkSwitch) { //allows the button to be held down and intake toggles once
		intkSwitch = false;
		intkPos = !intkPos;
		setIntk(intkPos);
	}

    if(master.get_digital(E_CONTROLLER_DIGITAL_A))
		setLock(0);
	else
		setLock(!intkPos);

	if(r2())
        liftStat = LiftStatus::stack;

}