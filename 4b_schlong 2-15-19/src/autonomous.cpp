#include "main.h"

void autonomous() { //15 second autonomous period at the beginning of the match

    turn(90, 0, 1500, 100);
    //find the max acceleration
    /*runBaseVel(200, 100);
    for(int i = 0; i < 2000; i++) {
        std::cout << leftBase1.get_actual_velocity() << " | " << rightBase1.get_actual_velocity() << " | " << i  << std::endl;
        delay(1);
    }
    runBaseVel(0, 0);*/
    //curveBaseVel(200, 100, 15);

    //curving with voltage
    /*curveBase(-15, -100, 19);
    curveBase(-100, -15, 21);
    moveStraight(-2, 0, 500);*/

}