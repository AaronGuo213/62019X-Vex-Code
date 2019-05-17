#include "main.h"

float findTheta(float x, float y) {

    float theta;

    if(x >= 6 || y >= 6) {

        if(x == 0) {
            
            if(y >= 6)
                theta = 90;
            else if(y <= -6)
                theta = 270;

        }

        else if(y == 0) {

            if(x >= 6)
                theta = 0;
            if(x <= -6)
                theta = 180;

        }

        else if(y > 0) {
            
            theta = atan(y / x);

        }

        else if(y < 0) {

            theta = atan(y / x) + 180;

        }

    }

}


float joyValRemap(float joyVal) {

    float percentVal = 0.0;

    if((float)joyVal <= -3.0) {

        percentVal = pow(-pow((float)joyVal, 2) - 6 * (float)joyVal + 18327.7, 0.5) - 154.414;

    }

    else if((float)joyVal >= 3.0) {

        percentVal = -pow(-pow((float)joyVal, 2) + 6 * (float)joyVal + 18327.7, 0.5) + 154.414;

    }

    else {

        percentVal = 0.0;

    }

    return percentVal;

}