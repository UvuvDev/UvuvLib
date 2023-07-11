#include "UvuvLib/UvuvController.h"

UvuvBasicController::UvuvBasicController() {

}

UvuvBasicController::UvuvBasicController(pros::controller_id_e_t controllerID, pros::Controller* controllerArg) {
    if (controllerArg == nullptr) {
        prosController = new pros::Controller(controllerID);
    } else {
        prosController = controllerArg;
    }

}

UvuvBasicController::~UvuvBasicController() {
    delete prosController;
}

bool UvuvBasicController::getButtonCombination(pros::controller_digital_e_t button, pros::controller_digital_e_t button2) {
    return prosController->get_digital(button) && prosController->get_digital(button2);
}

bool UvuvBasicController::getButtonCombination(pros::controller_digital_e_t button, pros::controller_digital_e_t button2, pros::controller_digital_e_t button3) {
    return prosController->get_digital(button) && prosController->get_digital(button2) && prosController->get_digital(button3);
}

bool UvuvBasicController::newButtonPress(pros::controller_digital_e_t button) {
    
    static bool buttonState = false;
    static bool buttonStateLastTick = false;

    buttonStateLastTick = buttonState;

    buttonState = prosController->get_digital(button);

    if (buttonState != buttonStateLastTick) {
        return true;
    }

    else {
        return false;
    }

}

bool UvuvBasicController::toggleButton(pros::controller_digital_e_t button) {

    static int toggleState = 0;

    if (newButtonPress(button)) {
        toggleState++;
    }
    
    if (toggleState % 2 == 0) {
        return true;
    }

    else {
        return false;
    }

}

void UvuvBasicController::rumble() {
    prosController->rumble("-");
}

bool UvuvBasicController::getButton(pros::controller_digital_e_t button) {
    return prosController->get_digital(button);
}

bool UvuvBasicController::getJoystick(pros::controller_analog_e_t whichJoystick) {
    return prosController->get_analog(whichJoystick);
}


pros::Controller* UvuvBasicController::getController() {
    return prosController;
}

















UvuvAdvancedController::UvuvAdvancedController(pros::controller_id_e_t controllerID, std::vector<std::string> modesParam,
    pros::Controller* controllerArg) {

        if (controllerArg == nullptr) {
            prosController = new pros::Controller(controllerID);
        } else {
            prosController = controllerArg;
        }

        modes = modesParam;

        for (int i = 0; i < modesParam.size(); i++) {
            addMode(modesParam[i]);
        }
    
    
    }



UvuvAdvancedController::~UvuvAdvancedController() {
    delete prosController;
}


std::vector<std::string> UvuvAdvancedController::getModes() {
    return modes;
}


void UvuvAdvancedController::addMode(std::string modeParam) {
    modes.push_back(modeParam);
}



void UvuvAdvancedController::setFuncToButton(int(*functionPtr)(), pros::controller_digital_e_t button) {

    std::pair<pros::controller_digital_e_t, int(*)()> buttonFuncPair(button, functionPtr);

    buttonsToFunctions.push_back(buttonFuncPair);

}

