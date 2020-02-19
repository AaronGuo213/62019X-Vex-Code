#include "main.h"

Controller master (CONTROLLER_MASTER); //main controller
Controller partner (CONTROLLER_PARTNER);

//V5 Components
Motor leftBase1(2, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor
Motor leftBase2(16, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor
Motor rightBase1(1, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//200 rom motor
Motor rightBase2(17, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor

Motor lift(21, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 
//100 rpm motor

Motor leftIntk(9, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor
Motor rightIntk(6, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor

Motor tray(5, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES);
//100 rpm motor

Imu imu(10);


//Legacy Components
ADIEncoder yawEnc(7, 8, 0); //wheel encoder in ports 7 and 8
ADIEncoder leftEnc(3, 4, 1); //wheel encoder in ports 5 and 6
ADIEncoder rightEnc(1, 2, 1); //wheel encoder in ports 1 and 2