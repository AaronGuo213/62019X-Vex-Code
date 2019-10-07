#include "main.h"

void blue3() { //autonomous for the four in a row

    liftSetPoint = 600;
    moveStraight(20, 1000, 80);
    liftSetPoint = 300;
    delay(1000);
    liftSetPoint = 500;
    delay(1000);
    moveStraight(-11, 3000, 50);
    turn(-90, 1500, 40);
    moveStraight(60, 1700, 80); //moves to goal and lowers lift to the ground
    liftSetPoint = 300;
    moveStraight(12, 1200, 40); //inches forward to move the cubes past the ramp
    setIntk(0); //outtakes and backs up
    delay(500);
    moveStraight(-20, 1000, 60);
    
}