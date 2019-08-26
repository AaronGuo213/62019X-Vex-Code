#ifndef PRAGMA_H
#define PRAGMA_H

extern Controller master;

//V5 Components
extern Motor leftBase1;
extern Motor leftBase2;
extern Motor rightBase1;
extern Motor rightBase2;

extern Motor leftLift;
extern Motor rightLift;
extern Motor claw1;
extern Motor claw2;

//Legacy Components
extern ADIAnalogIn liftPot;
extern ADIUltrasonic cubeSensor;
extern ADIEncoder yawEnc;
extern ADIDigitalOut intk1;
extern ADIDigitalOut intk2;

#endif