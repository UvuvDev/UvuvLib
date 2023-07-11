#pragma once

#include "main.h"

#include "PID.h"
#include "Motor.h"
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

    float HausdorffDimension = 0; // The Hausdorff Dimension, the measure of how rough the graph is.

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

    Gearing gearing;

    float kP; 
    float kI;
    float kD;
    
    UvuvGeneralPIDTuner();

    /**
     * @brief Calculate the Hausdorff Dimension of the graph.
     * 
     */
    void calculateHausdorffDimension(); 

    /**
     * @brief Calculate kP with either calculating the Hausdorff Dimension or through guessing and testing until the target
     * RPM matches the output, depending on the PID type.
     * 
     * Dimensions = log N / log 1/h, where N is the number of grid boxes that overlap the graph and h is the number of grid boxes.
     *
     */
    void calculateP();

    /**
     * @brief TEMPORARILY NOT USED. WILL BE SUPPORTED IN THE FUTURE.
     * 
     */
    void calculateI();

    /**
     * @brief Calculate kD by finding how low the overshoot can go without affecting the difference between target RPM and actual RPM,
     * or getting how close the graph is to a straight line, depending on the PID type.
     *
     * TargetRPM - ActualRPM = Difference, Difference - CONSTANT > 0 or else the D is tuned.
     * 
     */
    void calculateD();
    
public:

    /**
     * @brief Construct a new Uvuv General PID Tuner object
     * 
     * @param type The type of PID you want to tune. Specified using DesiredPIDType enum.
     * @param untunedPIDController The PID Controller being used.
     * @param uvuvMotorPtr UvuvMotor pointer.
     */
    UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, UvuvMotor* uvuvMotorPtr);

    /**
     * @brief Construct a new Uvuv General PID Tuner object
     * 
     * @param type The type of PID you want to tune. Specified using DesiredPIDType enum.
     * @param untunedPIDController The PID Controller being used.
     * @param uvuvMotorPtr UvuvMotor Group pointer.
     */
    UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, UvuvMotorGroup* uvuvMotorGroupPtr);

    /**
     * @brief Construct a new Uvuv General PID Tuner object
     * 
     * @param type The type of PID you want to tune. Specified using DesiredPIDType enum.
     * @param untunedPIDController The PID Controller being used.
     * @param uvuvMotorPtr PROS Motor pointer.
     */
    UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, pros::Motor* prosMotorPtr, Gearing gearingArg);

    /**
     * @brief Construct a new Uvuv General PID Tuner object
     * 
     * @param type The type of PID you want to tune. Specified using DesiredPIDType enum.
     * @param untunedPIDController The PID Controller being used.
     * @param uvuvMotorPtr UvuvMotor pointer.
     */
    UvuvGeneralPIDTuner(DesiredPIDType type, PIDController* untunedPIDController, pros::MotorGroup* prosMotorGroupPtr, Gearing gearingArg);


    ~UvuvGeneralPIDTuner();

    /**
     * @brief Returns in order: kP, kI, kD
     * 
     * @return std::vector<float> 
     */
    PIDConstants generatePIDValues();

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