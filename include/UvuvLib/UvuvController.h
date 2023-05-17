#pragma once

#include "main.h"


class UvuvController {
private:

protected:

    pros::Controller* prosController;

public:

    UvuvController(pros::controller_id_e_t controllerID);
    
    ~UvuvController();

    bool getButtonCombination(pros::controller_digital_e_t button, pros::controller_digital_e_t button2);

    bool getButtonCombination(pros::controller_digital_e_t button, pros::controller_digital_e_t button2, pros::controller_digital_e_t button3);

    void rumble();

    bool getButton(char button);

    bool getJoystick(pros::controller_analog_e_t whichJoystick);

    int getMode();

};