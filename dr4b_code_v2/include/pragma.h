#ifndef PRAGMA_H
#define PRAGMA_H

extern Controller master;

//V5 Components
extern Motor leftBase1; //four base motors
extern Motor leftBase2;
extern Motor rightBase1;
extern Motor rightBase2;

extern Motor leftLift; //left and right lift motors
extern Motor rightLift;


//Legacy Components
extern ADIAnalogIn liftPot; //potentiameter for lift control
extern ADIUltrasonic cubeSensor; //sonar sensor for cube depth input
extern ADIEncoder yawEnc; //encoder for horizontal movement
extern ADIDigitalOut intk; //a solonoid for four pistons
extern ADIDigitalOut rollers; //a solonoid for two pistons

#endif