#pragma once

#include "MotorGroup.h"
#include "PID.h"

#include "unordered_map"
#include <unordered_map>

class UvuvFlywheelController {
private:
    
    std::unordered_map<float, float, float> distanceToRPMandKV; 

    int voltage = 0;
    
protected:

public:

};