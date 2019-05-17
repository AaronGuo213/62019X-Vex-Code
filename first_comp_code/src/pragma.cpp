#include "main.h"

Controller master (CONTROLLER_MASTER); //master controller

//V5 Components
Motor westBase1(1, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 1
Motor westBase2(2, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 2
Motor eastBase1(3, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 3
Motor eastBase2(4, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 4

Motor lift1(6, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 6
Motor lift2(7, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 7
Motor claw(9, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 9

//Legacy Components
ADIAnalogIn liftPot(2); //potentiometer for lift in port 2
ADIDigitalIn leftEnc(4); //left wheel encoder in port 4
ADIDigitalIn rightEnc(5); //right wheel encoder in port 5
ADIDigitalIn yawEnc(6); //perpendicular wheel encoder in port 6