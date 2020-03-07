#include "main.h"

const double PI = 3.1415926535897932384626433832795028841971693993751058209749445923078;
const bool isSkills = false; //switch this to true to upload a skills version of code

int sgn(double x) { //returns -1, 1, or 0 for sign

    return (x > 0) - (x < 0);

}

double joyValRemap(double joyVal) {

    double percentVal;

    if((double)joyVal <= -3.0) //threshold at 3/100 to prevent unwanted movement at low values
        percentVal = pow(-pow((double)joyVal, 2) - 6 * (double)joyVal + 18327.7, 0.5) - 154.414; //uses the equation of a circle to optimize slow and fast movements

    else if((double)joyVal >= 3.0) //threshold at 3/100 to prevent unwanted movement at low values
        percentVal = -pow(-pow((double)joyVal, 2) + 6 * (double)joyVal + 18327.7, 0.5) + 154.414; //uses the reflected equation to optimize slow and fast backwards movements

    else
        percentVal = 0.0;

    return percentVal;

}

double speedToVolt(double rpm) {

    if(rpm > 5) //converts desired rpm to voltage
        return 0.455 * rpm + 8.18;
    if(rpm < 5)
        return 0.455 * rpm - 8.18;
    return 0;

}

PID initPID(bool useP, bool useI, bool useD, double kP, double kI, double kD) { //gives a created PID struct its values

    return { 0, 0, 0, 0, kP, kI, kD, useP, useI, useD };

}

double runPID(PID *pid) {

    pid->integral += pid->error; //increment integral by current error
    pid->derivative = pid->error - pid->prevError; //set derivative to the delta error
    pid->prevError = pid->error; //set prevError to current error to be used for next iteration
    double output = (pid->error * pid->kP * (double)pid->useP) + (pid->integral * pid->kI * (double)pid->useI) + (pid->derivative * pid->kD * (double)pid->useD); //calculate final value
    return output;

}

//buttons and joystick values

double lY(Controller cont) {
    return cont.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
}

double lX(Controller cont) {
    return cont.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
}

double rY(Controller cont) {
    return cont.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);
}

double rX(Controller cont) {
    return cont.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);
}

bool l1Pressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_L1);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_L1);
}

bool l2Pressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_L2);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_L2);
}

bool r1Pressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_R1);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_R1);
}

bool r2Pressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_R2);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_R2);
}

bool upPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_UP);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_UP);
}

bool downPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_DOWN);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN);
}

bool leftPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_LEFT);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT);
}

bool rightPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_RIGHT);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT);
}

bool aPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_A);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_A);
}

bool bPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_B);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_B);
}

bool xPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_X);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_X);
}

bool yPressed(Controller cont, bool newPress) {
    if(!newPress)
        return cont.get_digital(E_CONTROLLER_DIGITAL_Y);
    return cont.get_digital_new_press(E_CONTROLLER_DIGITAL_Y);
}