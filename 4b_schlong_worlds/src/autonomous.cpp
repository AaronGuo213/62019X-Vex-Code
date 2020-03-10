#include "main.h"

void autonomous() { //15 second autonomous period at the beginning of the match

    //random auton stuff to test
    //std::cout << getSonarInches(10) << std::endl;
    //moveDist(7, 30);
    //blueStack7();
    //redStack8();
    //redRow7();
    //redRow8();
    //redRow9();
    //blueRow9();
    /*runIntkDist(-160, 150);
    delay(300);
    moveTray(400);
    delay(1500);
    outtake();*/

    runBase(-60);
    delay(1000);
    runBase(60);
    delay(1000);
    runBase(0);

    tray.set_brake_mode(E_MOTOR_BRAKE_COAST);
    //decides which auton to run based on auton selector
    switch(autonCount) {
    
        case 0:
            redStack8();
            break;
        
        case 1:
            redRow7();
            break;

        case 2:
            redRow6();
            break;

        case 3:
            redStack7();
            break;

        case 4:
            skills();
            break;

        case 5:
            blueStack8();
            break;
        
        case 6:
            blueRow7();
            break;

        case 7:
            blueRow6();
            break;

        case 8:
            blueStack7();
            break;

        case 9:
            skills();
            break;

        default:
            break;

    }

}