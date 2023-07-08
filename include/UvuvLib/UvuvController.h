#pragma once

#include "main.h"



class UvuvBasicController {
private:

protected:

    pros::Controller* prosController;

    UvuvBasicController();

public:

    UvuvBasicController(pros::controller_id_e_t controllerID, pros::Controller* controllerArg = nullptr);
    
    ~UvuvBasicController();

    bool getButtonCombination(pros::controller_digital_e_t button, pros::controller_digital_e_t button2);

    bool getButtonCombination(pros::controller_digital_e_t button, pros::controller_digital_e_t button2, pros::controller_digital_e_t button3);

    bool newButtonPress(pros::controller_digital_e_t button);

    bool toggleButton(pros::controller_digital_e_t button);

    void rumble();

    bool getButton(pros::controller_digital_e_t button);

    bool getJoystick(pros::controller_analog_e_t whichJoystick);

    pros::Controller* getController();

};

class UvuvAdvancedController : public UvuvBasicController {
private:

protected:

    
    std::vector<std::string> modes;
    std::vector<std::pair<pros::controller_digital_e_t, int(*)()>> buttonsToFunctions; 

public: 

    UvuvAdvancedController(pros::controller_id_e_t controllerID, std::vector<std::string> modesParam, pros::Controller* controllerArg = nullptr);

    ~UvuvAdvancedController();

    std::vector<std::string> getModes();

    void addMode(std::string modeParam); 
    
    void setFuncToButton(int(*functionPtr)(), pros::controller_digital_e_t button);

};