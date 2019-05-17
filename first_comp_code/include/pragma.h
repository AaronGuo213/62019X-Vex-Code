#ifndef PRAGMA_H
#define PRAGMA_H

extern Controller master;

//V5 Components
extern Motor westBase1;
extern Motor westBase2;
extern Motor eastBase1;
extern Motor eastBase2;

extern Motor lift1;
extern Motor lift2;
extern Motor claw;

//Legacy Components
extern ADIAnalogIn liftPot;
extern ADIDigitalIn leftEnc;
extern ADIDigitalIn rightEnc;
extern ADIDigitalIn yawEnc;

#endif