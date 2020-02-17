#include "main.h"

void outtake() {

	trayStat = TrayStatus::manual;
    runIntk(0);
	while(getTrayPos() < 870) {
		runTray(calcTrayPow(1) + 5);
		delay(50);
	}
	runTray(0); //stops the tray

	//runBase(25, 25); //pushes the stack forward
	//delay(300);
	moveStraight(-10, 1, 1000, 60); //moves back
	runIntk(0);
	trayStat = TrayStatus::idle;

}