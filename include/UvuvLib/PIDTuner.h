#pragma once

#include "main.h"

#include "PID.h"
#include "Motor.h"
#include "MotorGroup.h"
#include "Filters.h"
#include "GraphingTool.h"
#include "Definitions.h"

#include <vector>

typedef enum {

    StableLiftPID = 1,
    DrivetrainTurnPID,
    DrivetrainDriveToPID,
    DrivetrainDriveStraightPID,
    FlywheelPID,
    GeneralPID

} DesiredPIDType;

enum class E_MotorAPI {

    UvuvMotor = 1,
    UvuvMotorGroup,
    ProsMotor,
    ProsMotorGroup

};

class UvuvGeneralPIDTuner {
protected:

    const char* graphName = "PID Tuner";
    const int waitTimeBetweenUpdate = 20;

    E_MotorAPI motorAPI;

    PIDController* pidController;

    UvuvMotor* uvuvMotor;
    UvuvMotorGroup* uvuvMotorGroup;
    
    pros::Motor* prosMotor;
    pros::MotorGroup* prosMotorGroup;

    int lastDeviationLevel;
    int deviationLevel;

    BasicFilter* filter;
    UvuvGraphingTool* graph;

    std::vector<float> deviationVector;

    Gearing gearing;

    float kP; 
    float kI;
    float kD;
    
    UvuvGeneralPIDTuner();

    float sinGraph(int index, float amplitude, float period, float verticalShift, float horizontalShift);

public:

    UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, UvuvMotor* uvuvMotorPtr);

    UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, UvuvMotorGroup* uvuvMotorGroupPtr);

    UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, pros::Motor* prosMotorPtr, Gearing gearingArg);

    UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, pros::MotorGroup* prosMotorGroupPtr, Gearing gearingArg);

    ~UvuvGeneralPIDTuner();

    /**
     * @brief Returns in order: kP, kI, kD
     * 
     * @return std::vector<float> 
     */
    std::vector<float> generatePIDValues();

};

class UvuvPIDFFTuner : public UvuvGeneralPIDTuner {
private:

    PIDFFController* pidFFController;

    float kV;

public:

    UvuvPIDFFTuner(DesiredPIDType type, PIDController* untunedPIDFFController);

    /**
     * @brief Returns in order: kV, kP, kI, kD
     * 
     * @return std::vector<float> 
     */
    std::vector<float> generatePIDValues();


};