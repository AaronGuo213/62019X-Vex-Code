#include "main.h"

void initialize() {

    delay(200);
    //Task liftGo (liftCtrl, (void*)"PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "lift control task"); //starts lift slow and hold tasks
    setIntk(1);

}

int autonCount = 0;

/*void lcdScroll() {

    if(autonCount > 6) { //loops the options

        autonCount = 0;

    }

    else if(autonCount < 0) { //loops the options

        autonCount = 6;

    }

    switch(autonCount) {

        case 0:
            lcd::set_text(2, "RED1\n");
            lcd::set_text(1, "4 Stack, 5 Cubes in Big Goal");
            break;

        case 1:
            lcd::set_text(2, "RED2\n");
            lcd::set_text(1, "Long L, 5 Cubes Unscored");
            break;

        case 2:
            lcd::set_text(2, "RED3\n");
            lcd::set_text(1, "4 in a Row, 5 Cubes in Small Goal");
            break;

        case 3:
            lcd::set_text(2, "BLUE1\n");
            lcd::set_text(1, "4 Stack, 5 Cubes in Big Goal");
            break;
            
        case 4:
            lcd::set_text(2, "BLUE2\n");
            lcd::set_text(1, "Long L, 5 Cubes Unscored");
            break;

        case 5:
            lcd::set_text(2, "BLUE3\n");
            lcd::set_text(1, "4 in a Row, 5 Cubes in Small Goal");
            break;

        case 6:
            lcd::set_text(1, "No Auton\n");
            break;

        default:
            lcd::set_text(1, "ERROR");
            break;

    }

}

void on_left_pressed() {

    autonCount--;
    lcdScroll();

}

void on_center_pressed() {

    lcd::shutdown();

}

void on_right_pressed() {

    autonCount++;
    lcdScroll();

}*/

void printController(int color, int type) {

    master.print(0, 0, "Choose Auton:");
    delay(100);
    switch (color) {
        case 0:
            master.print(1, 0, "*Red| Blu| N/A");
            break;
        case 1:
            master.print(1, 0, " Red|*Blu| N/A");
            break;
        case 2:
            master.print(1, 0, " Red| Blu|*N/A");
            break;
        default:
            break;
    }
    delay(100);
    switch (type) {
        case 0:
            master.print(2, 0, "*Col| L  | Row");
            break;
        case 1:
            master.print(2, 0, " Col|*L  | Row");
            break;
        case 2:
            master.print(2, 0, " Col| L  |*Row");
            break;
        default:
            break;
    }

}

void competition_initialize() {

    /*lcd::initialize();
    lcd::set_text(0, "choose auton");
    lcdScroll();
    lcd::register_btn0_cb(on_left_pressed);
    lcd::register_btn1_cb(on_center_pressed);
    lcd::register_btn2_cb(on_right_pressed);*/

    int color = 0, type = 0;
    while(!master.get_digital(E_CONTROLLER_DIGITAL_A)) {

        if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L2))
            color --;
        if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_R2))
            color ++;
        if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_L1))
            type --;
        if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1))
            type ++;
        color = color > 2 ? 0 : color;
        color = color < 0 ? 2 : color;
        type = type > 2 ? 0 : type;
        type = type < 0 ? 2 : type;
        autonCount = 3 * color + type;
        printController(color, type);
        delay(100);

    }

    master.clear_line(0);

}

void disabled() {

    

}