#ifndef INTAKE_H
#define INTAKE_H

void setIntk(bool status);
void setRollers(bool status);
void runRollers(float percent);
void rollerCtrl(void* param);

#endif