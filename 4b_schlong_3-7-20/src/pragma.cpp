#include "main.h"

Controller master (CONTROLLER_MASTER); //main controller
Controller partner (CONTROLLER_PARTNER);

/*===========
V5 COMPONENTS
===========*/
//base motors
Motor leftBase1(2, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor leftBase2(16, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor rightBase1(1, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
Motor rightBase2(17, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 

//intake motors
Motor leftIntk(9, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
Motor rightIntk(6, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES);

//tray motor
Motor tray(4, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES);

//lift motor
Motor lift(21, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 

//inertial sensor
Imu imu(3);


/*===============
Legacy Components
===============*/
//encoders
ADIEncoder yawEnc(7, 8, 0);
ADIEncoder leftEnc(3, 4, 1);
ADIEncoder rightEnc(1, 2, 1);

//sonar
ADIUltrasonic sonar(5, 6);