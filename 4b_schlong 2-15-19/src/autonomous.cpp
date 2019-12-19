#include "main.h"

void autonomous() { //15 second autonomous period at the beginning of the match

    //find the max acceleration
    runBaseVel(200, 100);
    delay(2000);
    runBaseVel(0, 0);

    //curving with voltage
    /*curveBase(100, 70, 15);*/

}