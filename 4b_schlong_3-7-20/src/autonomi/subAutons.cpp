#include "main.h"

void outtake() {

	trayStat = TrayStatus::manual;
    runIntk(0);
	while(getTrayPos() < 850) {
		runTray(calcTrayPowAuton(1));
		delay(50);
	}
	runTray(0); //stops the tray

	moveStraight(-10, 60); //moves back
	runIntk(0);
	trayStat = TrayStatus::idle;

}