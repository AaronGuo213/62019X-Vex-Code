#include "main.h"

void runIntk(double percent) {

    leftIntk.move_voltage(percent * 120);
	rightIntk.move_voltage(percent * 120);

}

void updateIntk() {

    if(l1() && !l2())
		runIntk(100);

	else if(l2() && !l1())
		runIntk(-100);

	else
		runIntk(0);

}

void runTray(double percent) {

    tray.move_voltage(percent * 120);
	
}

int getTrayPos() {

	return trayPot.get_value() - 0;
		
}

void updateTray() {

	if(r1() && !r2()) {
		runTray(getTrayPos());
	}

	else if(r2() && !r1()) {
		runTray(-1000 + getTrayPos());
	}

	else
		runTray(0);

}