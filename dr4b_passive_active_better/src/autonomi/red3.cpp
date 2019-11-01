#include "main.h"

void red3() { //autonomous for the four in a row

    moveLift(onCubes[1]); //stacks the first cube
    moveStraight(34, 1500, 90);
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(13, 1000, 60); //stacks the second cube
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(13, 1000, 60); //stacks the third cube
    liftStat = LiftStatus::stack;
    delay(1000);

    moveStraight(13, 1000, 60); //stacks the fourth cube
    liftStat = LiftStatus::uncontrolled;
    runLift(-100);
    while(getLiftHeight() > 20)
        delay(10);
    runLift(0);
    moveLift(onCubes[0]);

    moveStraight(-39, 2000, 50); //moves back and turns to the goal
    turn(-70, 1500, 60);
    moveStraight(50, 2000, 70); //runs into the goal and outtakes
    liftStat = LiftStatus::uncontrolled;
    runLift(-100);
    while(getLiftHeight() > 10)
        delay(10);
    runLift(0);
    delay(200);
    setIntk(0);
    delay(500);
    moveStraight(-50, 1000, 50);
    
}