#ifndef PRAGMA_H
#define PRAGMA_H

extern Controller master;

//V5 Components
extern Motor leftBase1; //four base motors
extern Motor leftBase2;
extern Motor rightBase1;
extern Motor rightBase2;

extern Motor lift; //lift motor

extern Motor leftIntk; //left and right intake motors
extern Motor rightIntk;

extern Motor tray; //tray motor

//Legacy Components
extern ADIAnalogIn liftPot; //potentiameter for lift control
extern ADIEncoder yawEnc; //encoder for horizontal movement
extern ADIEncoder leftEnc;
extern ADIEncoder rightEnc;

#endif