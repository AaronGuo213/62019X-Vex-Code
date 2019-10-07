#include "main.h"

void setIntk(bool status) {

    intk.set_value(status);
    lock.set_value(status);

}

void setLock(bool status) {

    lock.set_value(status);

}