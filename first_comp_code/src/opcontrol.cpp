#include "main.h"

void opcontrol() {

	float westBaseVal, eastBaseVal, r;

	while(true) {

		r = joyValRemap(pow(pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), 2) + pow(master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y), 2), 0.5));
		westBaseVal = westBaseRemap(r, findTheta(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)));
		eastBaseVal = eastBaseRemap(r, findTheta(master.get_analog(E_CONTROLLER_ANALOG_LEFT_X), master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y)));

		runWestBase(westBaseVal);
		runEastBase(eastBaseVal);

	}

}