#include "main.h"

Controller master (CONTROLLER_MASTER); //master controller

//V5 Components
Motor leftBase1(1, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 1
Motor leftBase2(2, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 2
Motor rightBase1(3, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 3
Motor rightBase2(4, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 4

Motor lift1(6, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 6
Motor lift2(7, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 7
Motor claw(9, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 9

//Legacy Components
ADIAnalogIn liftPot(2); //potentiometer for lift in port 2
ADIEncoder leftEnc(3, 4, 0); //left wheel encoder in ports 3 and 4
ADIEncoder rightEnc(5, 6, 0); //right wheel encoder in ports 5 and 6
ADIEncoder yawEnc(7, 8, 0); //perpendicular wheel encoder in ports 7 and 8