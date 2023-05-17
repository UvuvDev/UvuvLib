#pragma once
#include "main.h"
#include "pros/motors.h"

class UvuvMotor {
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

    void spinAtVoltage(int voltage);

    void spinPerc(int percent);

    void spinJoystick(int joystickValue);

    void spinPercVEXPID(int percent);

    void spinAtRPM(int RPM);

    void spinDistance(float distanceInches);

    void spinUntilDegree(int degree, int speedInVoltage);

    void spinFor(float seconds, int speedInVoltage);

    void logMotorPerformance(); // Stuff like wattage and temperature, RPM, etc, along with Port Number

    void shutDown();

    void revive();

    bool getIsBroken();

    bool isOverheated();

    float getRPM();

    float getVoltage();
    
    
};