#include "main.h"

Controller master (CONTROLLER_MASTER); //master controller

//V5 Components
Motor leftBase1(14, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 1
Motor leftBase2(5, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 2
Motor rightBase1(16, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 3
Motor rightBase2(7, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 4

Motor leftLift(11, MOTOR_GEARSET_36, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 6
Motor rightLift(12, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 7

//Legacy Components
ADIAnalogIn liftPot(3); //potentiometer for right side of lift in port 3
ADIEncoder yawEnc(7, 8, 0); //perpendicular wheel encoder in ports 7 and 8
ADIDigitalOut intk1(4);
ADIDigitalOut intk2(5);