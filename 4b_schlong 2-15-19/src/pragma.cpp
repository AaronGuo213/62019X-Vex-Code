#include "main.h"

Controller master (CONTROLLER_MASTER); //main controller
Controller partner (CONTROLLER_PARTNER);

//V5 Components
Motor leftBase1(1, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor
Motor leftBase2(11, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor
Motor rightBase1(3, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//200 rom motor
Motor rightBase2(12, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor

Motor lift(20, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 
//100 rpm motor

Motor leftIntk(21, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor
Motor rightIntk(5, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor

Motor tray(8, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES);
//100 rpm motor


//Legacy Components
ADIAnalogIn liftPot(4); //potentiometer in port 4
ADIEncoder yawEnc(7, 8, 1); //wheel encoder in ports 7 and 8
ADIEncoder leftEnc(5, 6, 1); //wheel encoder in ports 5 and 6
ADIEncoder rightEnc(1, 2, 0); //wheel encoder in ports 1 and 2