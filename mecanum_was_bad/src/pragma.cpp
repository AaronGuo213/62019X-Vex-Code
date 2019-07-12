#include "main.h"

Controller master (CONTROLLER_MASTER); //master controller

//V5 Components
Motor leftBase1(1, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 1
Motor leftBase2(2, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 2
Motor rightBase1(3, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 3
Motor rightBase2(4, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 4

Motor leftLift(6, MOTOR_GEARSET_36, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 6
Motor rightLift(7, MOTOR_GEARSET_36, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 7

Motor claw1(9, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 9
Motor claw2(10, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 10

//Legacy Components
ADIAnalogIn liftPotLeft(2); //potentiometer for left side of lift in port 2
ADIAnalogIn liftPotRight(3); //potentiometer for right side of lift in port 3
ADIUltrasonic cubeSensor(5, 6); //sonar sensor with ping in port 3 and echo in port 4
ADIEncoder yawEnc(7, 8, 0); //perpendicular wheel encoder in ports 7 and 8