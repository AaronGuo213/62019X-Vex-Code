#include "main.h"

void runTray(double percent) {

    tray.move_voltage(percent * 120);
	
}

int getTrayPos() {

	return tray.get_position();
		
}

 //calculates the power to send to the tray motor for a consistent outtaking process
double calcTrayPow(bool moveForward) {

	if(moveForward && getTrayPos() < 950)
		return(950 - getTrayPos()) / 8.5 + 10;

	if(!moveForward && getTrayPos() > 0)
		return -getTrayPos();

	return 0;

}

void traySafetyNet() {

	if(tray.is_over_temp())
		tray.set_voltage_limit(0);
	else 
		tray.set_voltage_limit(12000);

}

double traySetPoint = 0;
bool resetTrayIntegral = false;
enum class TrayStatus;
TrayStatus trayStat = TrayStatus::idle;

void ctrlTray(void* param) { //tray control task

	std::uint32_t now = millis();
	PID hold = initPID(1, 0, 0, 1, 0, 0); //kP = 0.3, kI = 0.0001
	double holdVal;

	while(true) {

		traySetPoint = traySetPoint > 950 ? 950 : traySetPoint; //lift cannot be higher than 1800
        traySetPoint = traySetPoint < 0 ? 0 : traySetPoint; //lift cannot be lower than 0

		if(resetTrayIntegral) {
            hold.integral = 0;
            resetIntegral = false;
        }

		if(trayStat != TrayStatus::manual) {

			if(trayStat == TrayStatus::idle) { //doesnt make the tray hold the position, lets the motor rest
				runTray(0);
			}

			else if(trayStat == TrayStatus::hold) { //holds the tray in place
				hold.error = (traySetPoint - getTrayPos()); //updates error for holdPID
                holdVal = runPID(&hold); //updates the holdVal, reference misc.cpp
                runTray(holdVal);
				//std::cout << "traySetPoint: " << traySetPoint << " | trayPos: " << getTrayPos() << " | hold.error: " << hold.error << " | holdVal: " << holdVal << std::endl;
			}

		}

		traySafetyNet();
		Task::delay_until(&now, 50);

	}

}

void updateTray() {

	if(r2() && !l2()) { //r1 pressed runs the tray outward
		trayStat = TrayStatus::manual;
		runTray(calcTrayPow(1));
	}

	else if(l2() && !r2()) { //r2 pressed runs the tray inward
		trayStat = TrayStatus::manual;
		runTray(calcTrayPow(0));
	}

	else 
		trayStat = TrayStatus::idle;

	/*(else if(getTrayPos() < 200) {
		trayStat = TrayStatus::idle;
	}

	else if(trayStat == TrayStatus::manual) { //otherwise dont run the tray motor
		traySetPoint = getTrayPos();
		trayStat = TrayStatus::hold;
	}*/

	traySafetyNet();

}

void setTrayHold(bool updateSetPoint) {

	trayStat = TrayStatus::hold;
	if(updateSetPoint)
		traySetPoint = getTrayPos();

}

void setTrayIdle() {

	trayStat = TrayStatus::idle;

}

void moveTray(int setPoint) {

	trayStat = TrayStatus::hold;
	traySetPoint = setPoint;

}