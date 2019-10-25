#include "main.h"

Controller master (CONTROLLER_MASTER); //main controller

//V5 Components
Motor leftBase1(3, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor in port 1 for powering the left side of the base
Motor leftBase2(11, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); 
//reversed 200 rpm motor in port 2 for powering the left side of the base
Motor rightBase1(9, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//reversed 200 rpm motor in port 3 for powering the right side of the base
Motor rightBase2(20, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); 
//200 rpm motor in port 5 for powering the right side of the base

Motor leftLift(18, MOTOR_GEARSET_36, 0, E_MOTOR_ENCODER_DEGREES); 
//100 rpm motor in port 11 for powering the left side of the lift
Motor rightLift(17, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); 
//reversed 100 rpm motor in port 12 for powering the right side of the lift


//Legacy Components
ADIAnalogIn liftPot(6); //potentiometer in port 3 for the lift
ADIAnalogIn cubeSensor(5); //line sensor in port 6 for detecting a certain number of cubes
ADIEncoder yawEnc(2, 3, 0); //perpendicular wheel encoder in ports 7 and 8
ADIDigitalOut intk(7); //solonoid in port 4 for activating and deactivating the intake
ADIDigitalOut lock(8); //solonoid in port 5 for activating and deactivating the cube lock
ADIDigitalIn liftSwitch(4); //limit switch in port 5 for the lift