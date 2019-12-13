#include "main.h"

void autonomous() { //15 second autonomous period at the beginning of the match

    switch(autonCount) {

        case 0:
            deploy();
            redStack8();
            break;
        
        case 1:
            deploy();
            redRow8();
            break;

        case 2:
            deploy();
            redRow6();
            break;

        case 4:
            deploy();
            blueStack8();
            break;
        
        case 5:
            deploy();
            blueRow8();
            break;

        case 6:
            deploy();
            blueRow6();
            break;

        default:
            break;

    }
    
}