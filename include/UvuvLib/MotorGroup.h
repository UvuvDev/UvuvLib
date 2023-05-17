#pragma once

#include "Definitions.h"
#include "Motor.h"

class UvuvMotorGroup {
private:
    
    std::vector<UvuvMotor*> motorContainer;

public:

    UvuvMotorGroup(std::vector<UvuvMotor*> motorContainerArg);

    UvuvMotorGroup(std::vector<std::pair<int, motorRotation>> motorParameters);

};