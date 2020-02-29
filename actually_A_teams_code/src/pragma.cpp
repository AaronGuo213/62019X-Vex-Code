#include "main.h"

Controller master (CONTROLLER_MASTER); //master controller

//V5 Components
Motor leftBase1(5, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 1
Motor leftBase2(3, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 2
Motor rightBase1(10, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 3
Motor rightBase2(4, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 4

Motor intk1(14, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES);
Motor intk2(13, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES);
Motor tray(18, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES);
Motor arms(20, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES);