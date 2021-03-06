#include "main.h"

Controller master (CONTROLLER_MASTER); //main controller
Controller partner (CONTROLLER_PARTNER);

//V5 Components
Motor leftBase1(1, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor in port 1 for powering the left side of the base
Motor leftBase2(11, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//reversed 200 rpm motor in port 2 for powering the left side of the base
Motor rightBase1(3, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//reversed 200 rpm motor in port 3 for powering the right side of the base
Motor rightBase2(12, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor in port 5 for powering the right side of the base

Motor lift(20, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 
//100 rpm motor in port 11 for powering the left side of the lift

Motor leftIntk(21, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor in port 11 for powering the left intake
Motor rightIntk(5, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//reversed 200 rpm motor in port 12 for powering the right intake

Motor tray(8, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES);
//100 rpm motor in port 4 for powering the tray


//Legacy Components
ADIAnalogIn liftPot(4); //potentiometer in port 6 for the lift
ADIEncoder yawEnc(7, 8, 1); //perpendicular wheel encoder in ports 2 and 3
ADIEncoder leftEnc(5, 6, 1); //left wheel encoder in ports 4 and 5
ADIEncoder rightEnc(1, 2, 0); //right wheel encoder in ports 6 and 7