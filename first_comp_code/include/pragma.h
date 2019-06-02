#ifndef PRAGMA_H
#define PRAGMA_H

extern Controller master;

//V5 Components
extern Motor leftBase1;
extern Motor leftBase2;
extern Motor rightBase1;
extern Motor rightBase2;

extern Motor lift1;
extern Motor lift2;
extern Motor claw1;

//Legacy Components
extern ADIAnalogIn liftPot;
extern ADIDigitalIn liftLimit;
extern ADIUltrasonic cubeSensor;
extern ADIEncoder aftEnc;
extern ADIEncoder yawEnc;

#endif