#include "UvuvLib/Motor.h"

UvuvMotorGroup::UvuvMotorGroup(std::vector<UvuvMotor*> motorContainerArg) {

}


UvuvMotorGroup::UvuvMotorGroup(std::vector<std::pair<int, motorRotation>> motorParameters) {

    
}


void UvuvMotorGroup::spinAtVoltage(int voltage) {

    static bool isAnyBroken = false;
    
    for (int i = 0; i < motorContainer.size(); i++) {
        if (motorContainer[i]->getIsBroken()) {
            isAnyBroken = true;
        }
    }

    if (!isAnyBroken) {
        for (int i = 0; i < motorContainer.size(); i++) {
            motorContainer[i]->spinAtVoltage(voltage);
        }
    }


}



void UvuvMotorGroup::spinPerc(int percent) {

    static bool isAnyBroken = false;
    
    for (int i = 0; i < motorContainer.size(); i++) {
        if (motorContainer[i]->getIsBroken()) {
            isAnyBroken = true;
        }
    }

    if (!isAnyBroken) {
        for (int i = 0; i < motorContainer.size(); i++) {
            motorContainer[i]->spinPerc(percent);
        }
    }
}



void UvuvMotorGroup::spinJoystick(int joystickValue) {

    static bool isAnyBroken = false;
    
    for (int i = 0; i < motorContainer.size(); i++) {
        if (motorContainer[i]->getIsBroken()) {
            isAnyBroken = true;
        }
    }

    if (!isAnyBroken) {
        for (int i = 0; i < motorContainer.size(); i++) {
            motorContainer[i]->spinJoystick(joystickValue);
        }
    }

}



void UvuvMotorGroup::spinPercVEXPID(int percent) {

    static bool isAnyBroken = false;
    
    for (int i = 0; i < motorContainer.size(); i++) {
        if (motorContainer[i]->getIsBroken()) {
            isAnyBroken = true;
        }
    }

    if (!isAnyBroken) {
        for (int i = 0; i < motorContainer.size(); i++) {
            motorContainer[i]->spinPercVEXPID(percent);
        }
    }

}



void UvuvMotorGroup::spinAtRPM(int RPM) {

    static bool isAnyBroken = false;
    
    for (int i = 0; i < motorContainer.size(); i++) {
        if (motorContainer[i]->getIsBroken()) {
            isAnyBroken = true;
        }
    }

    if (!isAnyBroken) {
        for (int i = 0; i < motorContainer.size(); i++) {
            motorContainer[i]->spinAtRPM(RPM);
        }
    }

}



void UvuvMotorGroup::spinUntilDegree(int degree, int speedInVoltage) {

    static bool isAnyBroken = false;
    
    for (int i = 0; i < motorContainer.size(); i++) {
        if (motorContainer[i]->getIsBroken()) {
            isAnyBroken = true;
        }
    }

    if (!isAnyBroken) {
        for (int i = 0; i < motorContainer.size(); i++) {
            motorContainer[i]->spinUntilDegree(degree, speedInVoltage);
        }
    }

}



void UvuvMotorGroup::spinFor(float seconds, int speedInVoltage) {

    static bool isAnyBroken = false;
    
    for (int i = 0; i < motorContainer.size(); i++) {
        if (motorContainer[i]->getIsBroken()) {
            isAnyBroken = true;
        }
    }

    if (!isAnyBroken) {
        for (int i = 0; i < motorContainer.size(); i++) {
            motorContainer[i]->spinFor(seconds, speedInVoltage);
        }
    }


}



void UvuvMotorGroup::logMotorPerformance() {


}

void UvuvMotorGroup::set_zero_position(int position) {

    for (int i = 0; i < motorContainer.size(); i++) {
        motorContainer[i]->set_zero_position(position);
    }
    

}



void UvuvMotorGroup::shutDown() {
    
    for (int i = 0; i < motorContainer.size(); i++) {
        motorContainer[i]->shutDown();
    }

}



void UvuvMotorGroup::revive() {

    for (int i = 0; i < motorContainer.size(); i++) {
        motorContainer[i]->revive();
    }

}


bool UvuvMotorGroup::isOverheated() {

    for (int i = 0; i < motorContainer.size(); i++) {
        if (motorContainer[i]->isOverheated()) {
            return true;
        }
    }

    return false;

}


std::vector<bool> UvuvMotorGroup::getIsBroken() {

    std::vector<bool> isBrokenContainer;

    for (int i = 0; i < motorContainer.size(); i++) {
        isBrokenContainer.push_back(motorContainer[i]->getIsBroken());
    }

    return isBrokenContainer;

}


std::vector<float> UvuvMotorGroup::getIndividualRPM() {

    std::vector<float> RPMContainer;

    for (int i = 0; i < motorContainer.size(); i++) {
        RPMContainer.push_back(motorContainer[i]->getRPM());
    }

    return RPMContainer;

}


float UvuvMotorGroup::getAverageRPM() {

    float averageRPM = 0;

    for (int i = 0; i < motorContainer.size(); i++) {
        averageRPM += motorContainer[i]->getRPM();
    }

    averageRPM /= motorContainer.size();

    return averageRPM;

}


float UvuvMotorGroup::getVoltage() {

    float voltage = 0;

    for (int i = 0; i < motorContainer.size(); i++) {
        voltage += motorContainer[i]->getVoltage();
    }

    voltage /= motorContainer.size();

    return voltage;

}


PIDController* UvuvMotorGroup::getDrivePID() {
    return drivePID;
}


PIDController* UvuvMotorGroup::getTurnPID() {
    return turnPID;
}


bool UvuvMotorGroup::assignDrivePID(PIDController pid) {
    drivePID = &pid;
}


bool UvuvMotorGroup::assignTurnPID(PIDController pid) {
    turnPID = &pid;
}


float UvuvMotorGroup::getAverageEncoderPositions() {
    
    float averageEncoderPositions = 0;

    for (int i = 0; i < motorContainer.size(); i++) {
        averageEncoderPositions += motorContainer[i]->getEncoderPos();
    }

    averageEncoderPositions /= motorContainer.size();

    return averageEncoderPositions;


}