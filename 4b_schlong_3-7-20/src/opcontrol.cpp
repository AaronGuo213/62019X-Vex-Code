#include "main.h"

void opcontrol() {

	std::uint_least32_t now = millis();
	liftSetPoint = getLiftHeight();
	resetBaseEnc();
	Odometry* tracker = new Odometry(0, 0, 0);
	Task trackingGo(trackPos, tracker, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "position tracking task");

	while(true) {

		//update functions
		updateBase();
		updateLift();
		updateIntk();
		updateTray();

		if(!imu.is_calibrating()) {
			c::imu_accel_s_t accel = imu.get_accel();
			c::imu_gyro_s_t gyro = imu.get_gyro_rate();
			std::cout << "x: " << accel.x << " |\ty: " << accel.y << " |\tz: " << accel.z << std::endl;
			std::cout << "x: " << gyro.x << " |\ty: " << gyro.y << " |\tz: " << gyro.z << std::endl;
			std::cout << "rotation: " << imu.get_rotation() << std::endl;
			std::cout << "yaw: " << imu.get_yaw() << " |\tpitch: " << imu.get_pitch() << " |\troll: " << imu.get_roll() << std::endl;
		}
		else 
			std::cout << "calibrating\n";

		//std::cout << sonar.get_value() << std::endl;
		//std::cout << getLeftEnc() << " | " << getRightEnc() << std::endl;
		//std::cout << getTrayPos() << std::endl;
		//std::cout << getLiftHeight() << std::endl;
		Task::delay_until(&now, 10);

	}

}