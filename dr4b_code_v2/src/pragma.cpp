#include "main.h"

Controller master (CONTROLLER_MASTER); //main controller

//V5 Components
Motor leftBase1(1, MOTOR_GEARSET_36, 0, E_MOTOR_ENCODER_DEGREES); 
//100 rpm motor in port 1 for powering the left side of the base
Motor leftBase2(2, MOTOR_GEARSET_36, 0, E_MOTOR_ENCODER_DEGREES); 
//reversed 100 rpm motor in port 2 for powering the left side of the base
Motor rightBase1(3, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 
//reversed 100 rpm motor in port 3 for powering the right side of the base
Motor rightBase2(6, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 
//100 rpm motor in port 5 for powering the right side of the base

Motor leftLift(11, MOTOR_GEARSET_36, 0, E_MOTOR_ENCODER_DEGREES); 
//100 rpm motor in port 11 for powering the left side of the lift
Motor rightLift(12, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 
//reversed 100 rpm motor in port 12 for powering the right side of the lift


//Legacy Components
ADIAnalogIn liftPot(3); //potentiometer in port 3 for the lift
ADIEncoder yawEnc(7, 8, 0); //perpendicular wheel encoder in ports 7 and 8
ADIDigitalOut intk(4); //solonoid in port 4 for activating and deactivating the intake
ADIDigitalOut lock(5); //solonoid in port 5 for activating and deactivating the cube lock