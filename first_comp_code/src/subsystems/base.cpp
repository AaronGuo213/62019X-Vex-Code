#include "main.h"

void runWestBase(float westBaseVal) {

    westBase1.move_velocity(westBaseVal);
    westBase2.move_velocity(westBaseVal);

}

void runEastBase(float eastBaseVal) {

    eastBase1.move_velocity(eastBaseVal);
    eastBase2.move_velocity(eastBaseVal);

}

float westBaseRemap(float r, float theta) {

    theta += 45;
    float westBaseVal;

    if(abs(tan(theta)) <= 1)
        westBaseVal = r;

    else if(abs(tan(theta)) > 1)
        westBaseVal = r * cos(theta) / abs(sin(theta));

}

float eastBaseRemap(float r, float theta) {

    theta += 45;
    float eastBaseVal;

    if(abs(tan(theta)) >= 1)
        eastBaseVal = r;

    else if(abs(tan(theta)) < 1)
        eastBaseVal = r * sin(theta) / abs(cos(theta));

}