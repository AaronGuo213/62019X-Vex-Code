#include "main.h"

void autonomous() { //15 second autonomous period at the beginning of the match

    setIntk(0);
    delay(200);
    setIntk(1);
    delay(200);

    if(autonCount == 0)
        red1();

    else if(autonCount == 1)
        red2();
        
    else if(autonCount == 2)
        red3();
        
    else if(autonCount == 3)
        blue1();
        
    else if(autonCount == 4)
        blue2();
        
    else if(autonCount == 5)
        blue3();
    
}