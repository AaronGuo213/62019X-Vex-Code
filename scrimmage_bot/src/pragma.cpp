#include "main.h"

Controller master (CONTROLLER_MASTER); //master controller

//V5 Components
Motor leftBase1(11, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 1
Motor leftBase2(18, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 2
Motor rightBase1(21, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 3
Motor rightBase2(20, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES); //normal motor plugged into port 4

Motor intk1(12, MOTOR_GEARSET_18, 0, E_MOTOR_ENCODER_DEGREES);
Motor intk2(17, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES);
Motor tray(5, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES);
Motor arms(1, MOTOR_GEARSET_18, 1, E_MOTOR_ENCODER_DEGREES);