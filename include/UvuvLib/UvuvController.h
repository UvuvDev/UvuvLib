#pragma once

#include "main.h"



class UvuvBasicController {
private:

protected:

    pros::Controller* prosController;

public:

    UvuvBasicController(pros::controller_id_e_t controllerID);
    
  

    ~UvuvBasicController();

    bool getButtonCombination(pros::controller_digital_e_t button, pros::controller_digital_e_t button2);

    bool getButtonCombination(pros::controller_digital_e_t button, pros::controller_digital_e_t button2, pros::controller_digital_e_t button3);

    void rumble();

    bool getButton(char button);

    bool getJoystick(pros::controller_analog_e_t whichJoystick);

    

};

class UvuvAdvancedController : UvuvBasicController {
private:

protected:

    
    std::vector<std::string> modes;
    std::vector<std::pair<pros::controller_digital_e_t, int*>> buttonsToFunctions; 

public:

    

    UvuvAdvancedController(pros::controller_id_e_t controllerID, std::vector<std::string> modesParam);

    ~UvuvAdvancedController();

    std::string getMode();

    void setMode(std::string modeParam);
    
    void setFuncToButton();

    void start();

};