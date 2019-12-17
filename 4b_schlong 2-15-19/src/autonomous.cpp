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

        case 3:
            deploy();
            redStack7();
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

        case 7:
            deploy();
            blueStack7();
            break;

        case 8:
            deploy();
            break;
        
        case 12:
            deploy();
            break;

        default:
            break;

    }
    
}