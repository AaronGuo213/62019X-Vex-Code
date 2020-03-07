#ifndef PRAGMA_H
#define PRAGMA_H

extern Controller master;
extern Controller partner;

//V5 Components
extern Motor leftBase1; //four base motors
extern Motor leftBase2;
extern Motor rightBase1;
extern Motor rightBase2;

extern Motor lift; //lift motor

extern Motor leftIntk; //2 intake motors
extern Motor rightIntk;

extern Motor tray; //tray motor

extern Imu imu; //inertial sensor

//Legacy Components
extern ADIEncoder yawEnc; //encoder for horizontal movement
extern ADIEncoder leftEnc; //encoders for forward movement
extern ADIEncoder rightEnc;
extern ADIUltrasonic sonar; //sonar sensor for cube and corner detection

#endif