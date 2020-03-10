#include "main.h"

void outtake() {

	trayStat = TrayStatus::manual;
    runIntk(0);
	while(getTrayPos() < 850) { //outtakes cubes
		runTray(calcTrayPowAuton(1));
		delay(50);
	}
	runTray(0); //stops the tray

}

void outtakeSkills() {

	trayStat = TrayStatus::manual;
    runIntk(0);
	while(getTrayPos() < 850) {
		runTray(calcTrayPowAuton(1));
		delay(50);
	}
	runTray(0); //stops the tray

	delay(1000);
	moveDist(-12, 30); //moves back
	runIntk(0);

}