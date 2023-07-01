#pragma once
#include "main.h"
#include "pros/motors.h"
#include "Definitions.h"
#include "PID.h"

class UvuvMotorParent {
private:

    static constexpr int overheatTempCelsius = 55;

    bool isBroken = false;
    bool isReversed = false;
    bool hasPairMotor = false;

    int voltage = 0;

    float gearRatio = 0;

    pros::motor_gearset_e gearset = pros::E_MOTOR_GEAR_GREEN;

public:

    UvuvMotorParent();

    virtual void spinAtVoltage(int voltage) = 0;
 
    virtual void spinPerc(int percent) = 0;
 
    virtual void spinJoystick(int joystickValue) = 0;
 
    virtual void spinPercVEXPID(int percent) = 0;
 
    virtual void spinAtRPM(int RPM) = 0;
 
    virtual void spinDistance(float distanceInches) = 0;
 
    virtual void spinUntilDegree(int degree, int speedInVoltage) = 0;
 
    virtual void spinFor(float seconds, int speedInVoltage) = 0;
 
    virtual void logMotorPerformance() = 0; // Stuff like wattage and temperature, RPM, etc, along with Port Number

    virtual void set_zero_position(int position) = 0;
 
    virtual void shutDown() = 0;
 
    virtual void revive() = 0;
    
    virtual bool isOverheated();
    
};

class UvuvMotor : public UvuvMotorParent {
private:

    pros::Motor* motor;
    UvuvMotor* pairMotor;

    static constexpr int overheatTempCelsius = 55;

    bool isBroken = false;
    bool isReversed = false;
    bool hasPairMotor = false;

    int voltage = 0;

    float gearRatio = 0;

    pros::motor_gearset_e gearset = pros::E_MOTOR_GEAR_GREEN;

public:

    UvuvMotor(uint8_t port, bool isReversedArg, UvuvMotor* pairMotorArg = nullptr, float gearRatio = 1, pros::motor_gearset_e gearset = pros::E_MOTOR_GEAR_GREEN, bool pid = false);

    bool getIsBroken();

    float getRPM();

    float getVoltage();
    
    float getEncoderPos();
    
    
};

class UvuvMotorGroup : public UvuvMotorParent {
private:
    
    std::vector<UvuvMotor*> motorContainer;

    PIDController* drivePID;

    PIDController* turnPID;

public:

    UvuvMotorGroup(std::vector<UvuvMotor*> motorContainerArg);

    UvuvMotorGroup(std::vector<std::pair<int, motorRotation>> motorParameters);

    std::vector<bool> getIsBroken();

    std::vector<float> getIndividualRPM();

    float getAverageRPM();

    float getVoltage();

    PIDController getDrivePID();

    PIDController getTurnPID();

    bool assignDrivePID(PIDController pid);

    bool assignTurnPID(PIDController pid);

    float getAverageEncoderPositions();

};