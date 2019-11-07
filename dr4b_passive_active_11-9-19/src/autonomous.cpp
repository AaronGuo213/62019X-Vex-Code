#include "main.h"

void autonomous() { //15 second autonomous period at the beginning of the match

    setIntk(1);
    delay(200);
    
    switch (autonCount) {

        case 0:
            red1();
            break;

        case 1:
            red2();
            break;

        case 2:
            red3();
            break;

        case 4:
            blue1();
            break;

        case 5:
            blue2();
            break;

        case 6:
            blue3();
            break;

    }
    
}