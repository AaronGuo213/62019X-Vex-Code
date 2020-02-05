#include "main.h"

void runTray(double percent) {

    tray.move_voltage(percent * 120);
	
}

int getTrayPos() {

	return tray.get_position();
		
}

double calcTrayPow(bool moveForward) {

	//calculates the power to send to the tray motor for a consistent outtaking process
	if(moveForward && getTrayPos() < 875)
		//return (875 - getTrayPos()) / 6 + 10;
		return (875 - getTrayPos()) / 4 + 10;

	if(!moveForward && getTrayPos() > 0)
		return -getTrayPos();

	return 0;

}

void traySafetyNet() {

	//checks if the tray motor is over the safe temperature
	if(tray.is_over_temp())
		tray.set_voltage_limit(0);
	else 
		tray.set_voltage_limit(12000);

}

double traySetPoint = 0; //determines where the tray actively tries to move to
bool resetTrayIntegral = false;
enum class TrayStatus; //states for the current tray status
TrayStatus trayStat = TrayStatus::idle;

void ctrlTray(void* param) { //tray control task

	std::uint32_t now = millis();
	PID hold = initPID(1, 0, 0, 1, 0, 0); //kP = 1
	double holdVal;

	while(true) {

		traySetPoint = traySetPoint > 950 ? 950 : traySetPoint; //lift cannot be higher than 950
        traySetPoint = traySetPoint < 0 ? 0 : traySetPoint; //lift cannot be lower than 0

		if(resetTrayIntegral) {
			//prevents integral windup
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
				//debugging
				//std::cout << "traySetPoint: " << traySetPoint << " | trayPos: " << getTrayPos() << " | hold.error: " << hold.error << " | holdVal: " << holdVal << std::endl;
			}

		}

		//prevents the tray motor from overheating
		traySafetyNet();
		Task::delay_until(&now, 50);

	}

}

void updateTray() {

	if(r2Pressed() && !l2Pressed()) { //r2 pressed runs the tray outward
		trayStat = TrayStatus::manual;
		runTray(calcTrayPow(1));
	}

	else if(l2Pressed() && !r2Pressed()) { //l2 pressed runs the tray inward
		trayStat = TrayStatus::manual;
		runTray(calcTrayPow(0));
	}

	else //otherwise let the tray rest
		trayStat = TrayStatus::idle;

	/*(else if(getTrayPos() < 200) { //if the tray is not near the lowest point, hold its position
		trayStat = TrayStatus::idle;
	}

	else if(trayStat == TrayStatus::manual) { //otherwise dont run the tray motor
		traySetPoint = getTrayPos();
		trayStat = TrayStatus::hold;
	}*/

}

void setTrayHold(bool updateSetPoint) {

	//makes the tray hold its current position
	trayStat = TrayStatus::hold;
	if(updateSetPoint)
		traySetPoint = getTrayPos();

}

void setTrayIdle() {

	//lets the tray rest
	trayStat = TrayStatus::idle;

}

void moveTray(int setPoint) {

	//sets the setpoint for the tray and starts the PID loop
	trayStat = TrayStatus::hold;
	traySetPoint = setPoint;

}