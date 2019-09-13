#include "main.h"

Controller master (CONTROLLER_MASTER); //main controller

//V5 Components
Motor leftBase1(1, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor in port 1 for powering the left side of the base
Motor rightBase1(2, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//reversed 200 rpm motor in port 2 for powering the right side of the base

Motor leftLift(19, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 
//100 rpm motor in port 19 for powering the left side of the lift
Motor rightLift(20, MOTOR_GEARSET_36, 0, E_MOTOR_ENCODER_DEGREES); 
//reversed 100 rpm motor in port 20 for powering the right side of the lift

Motor leftRoller(6, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//reversed 200 rpm motor in port 6 for powering the left roller
Motor rightRoller(7, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor in port 7 for powering the right roller

//Legacy Components
ADIAnalogIn liftPot(3); //potentiometer in port 3 for the lift
ADIEncoder yawEnc(7, 8, 0); //perpendicular wheel encoder in ports 7 and 8
ADIDigitalOut intk(4); //solonoid in port 4 for activating and deactivating the intake
ADIDigitalOut rollers(5); //solonoid in port 5 for activating and deactivating the rollers