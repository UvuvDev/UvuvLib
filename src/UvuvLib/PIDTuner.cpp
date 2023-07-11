#include "UvuvLib/PIDTuner.h"
#include "UvuvLib/Definitions.h"
#include "UvuvLib/Math.h"
#include "UvuvLib/Motor.h"
#include <functional>

    
UvuvGeneralPIDTuner::UvuvGeneralPIDTuner() {

}

UvuvGeneralPIDTuner::UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, UvuvMotor* uvuvMotorPtr) {
    uvuvMotor = uvuvMotorPtr;
    pidController = untunedPIDController;
    motorAPI = E_MotorAPI::UvuvMotor;
    filter = new BasicFilter(6);
    graph = new UvuvGraphingTool(graphName, {0, 12000}, 20, true);
}

UvuvGeneralPIDTuner::UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, UvuvMotorGroup* uvuvMotorGroupPtr) {
    uvuvMotorGroup = uvuvMotorGroupPtr;
    pidController = untunedPIDController;
    motorAPI = E_MotorAPI::UvuvMotorGroup;
    filter = new BasicFilter(6);
    graph = new UvuvGraphingTool(graphName, {0, 12000}, 20, true);
}

UvuvGeneralPIDTuner::UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, pros::Motor* prosMotorPtr, Gearing gearingArg) {
    prosMotor = prosMotorPtr;
    pidController = untunedPIDController;
    motorAPI = E_MotorAPI::ProsMotor;
    gearing = gearingArg;
    filter = new BasicFilter(6);
    graph = new UvuvGraphingTool(graphName, {0, 12000}, 20, true);
}

UvuvGeneralPIDTuner::UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, pros::MotorGroup* prosMotorGroupPtr, Gearing gearingArg) {
    prosMotorGroup = prosMotorGroupPtr;
    pidController = untunedPIDController;
    motorAPI = E_MotorAPI::ProsMotorGroup;
    gearing = gearingArg;
    filter = new BasicFilter(6);
    graph = new UvuvGraphingTool(graphName, {0, 12000}, 20, true);
}

UvuvGeneralPIDTuner::~UvuvGeneralPIDTuner() {
    delete filter;
    delete graph;
}


PIDConstants UvuvGeneralPIDTuner::generatePIDValues() {

}





UvuvPIDFFTuner::UvuvPIDFFTuner(DesiredPIDType type, PIDController* untunedPIDFFController) {

}

  
std::vector<float> UvuvPIDFFTunergeneratePIDValues() {

}

