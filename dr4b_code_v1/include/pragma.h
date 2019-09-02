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
extern ADIAnalogIn leftLiftPot;
extern ADIAnalogIn rightLiftPot;
extern ADIUltrasonic cubeSensor;
extern ADIEncoder yawEnc;

#endif