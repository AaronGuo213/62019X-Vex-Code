#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();
	resetBaseEnc();
	Odometry* tracker = new Odometry(0, 0, 0);
	Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

	std::string infoStr;
	lv_style_t info;
    lv_style_copy(&info, &lv_style_plain);
    info.body.main_color = LV_COLOR_BLACK;
    info.body.grad_color = LV_COLOR_BLACK;
	info.text.color = LV_COLOR_RED;
	lv_obj_t *infoBox = lv_ta_create(lv_scr_act(), NULL);
	lv_obj_set_size(infoBox, 800, 400);
	lv_obj_set_pos(infoBox, 0, 0);
	lv_ta_set_style(infoBox, LV_TA_STYLE_BG, &info);

	while(true) {

		//update functions
		updateBase();
		updateLift();
		updateIntk();
		updateTray();

		infoStr = "";
		infoStr += "leftEnc: " + std::to_string(getLeftEnc()) + "     |     rightEnc: " + std::to_string(getRightEnc());
		infoStr += "\nisBaseStopped: " + std::to_string(isBaseStopped()) + "     |     isBaseSettled: " + std::to_string(isBaseSettled());

		infoStr += "\ngyro: " + std::to_string(imu.get_yaw());
		infoStr += "\nsonar: " + std::to_string(sonar.get_value());
		infoStr += "\nlift: " + std::to_string(getLiftHeight());
		infoStr += "\ntray: " + std::to_string(getTrayPos());
		lv_ta_set_text(infoBox, infoStr.c_str());

		//std::cout << sonarStr << std::endl;
		//std::cout << getLeftEnc() << " | " << getRightEnc() << std::endl;
		//std::cout << getTrayPos() << std::endl;
		//std::cout << getLiftHeight() << std::endl;
		Task::delay_until(&now, 10);

	}

}