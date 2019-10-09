#ifndef INTAKE_H
#define INTAKE_H

void setIntk(bool status);
void setLock(bool status);

extern bool intkSwitch, intkPos;
void updateIntk();

#endif