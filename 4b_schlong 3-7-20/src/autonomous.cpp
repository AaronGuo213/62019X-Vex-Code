#include "main.h"

void autonomous() { //15 second autonomous period at the beginning of the match

    //redStack7();
    //redStack8();
    //redRow7();
    //redRow8();
    //redRow9();
    //blueRow9();

    switch(autonCount) {
    
        case 0:
            redStack8();
            break;
        
        case 1:
            redRow9();
            break;

        case 2:
            redRow7();
            break;

        case 3:
            redStack7();
            break;

        case 4:
            blueStack8();
            break;
        
        case 5:
            blueRow9();
            break;

        case 6:
            blueRow7();
            break;

        case 7:
            blueStack7();
            break;

        default:
            break;

    }

}