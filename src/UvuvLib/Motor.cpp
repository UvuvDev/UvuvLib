#include "UvuvLib/Motor.h"

UvuvMotorParent::UvuvMotorParent() {

}

UvuvMotorParent::~UvuvMotorParent() {

}

UvuvMotor::UvuvMotor(uint8_t port, bool isReversedArg, Gearing gearRatioArg, pros::motor_gearset_e gearset, 
    UvuvMotor* pairMotorArg, PIDController* pidArg) {
        motor = new pros::Motor(port, gearset, isReversedArg);
        isReversed = isReversedArg;
        gearRatio = gearRatioArg;
        pairMotor = pairMotorArg;
        pid = pidArg;
        isBroken = false;

}

bool UvuvMotor::getIsBroken() {
    return isBroken;
}

float UvuvMotor::getRPM() {
    return motor->get_actual_velocity() * gearRatio;
}

float UvuvMotor::getVoltage() {
    return voltage;
}

float UvuvMotor::getEncoderPos() {
    return motor->get_position();
}

void UvuvMotor::spinAtVoltage(int voltage) {
    if (!isBroken) {
        motor->move_voltage(voltage);
    }
    
}

void UvuvMotor::spinPerc(int percent) {
    if (!isBroken) {
        motor->move_voltage(percent / 100 * 12000);
    }
}

void UvuvMotor::spinJoystick(int joystickValue) {
    if (!isBroken) {
        motor->move_voltage(joystickValue / 127 * 12000);
    }
}

void UvuvMotor::spinPercVEXPID(int percent) {
    if (!isBroken) {
        motor->move(voltage);
    }
}

void UvuvMotor::spinAtRPM(int RPM) {
    if (!isBroken) {
        pid->step(getRPM(), RPM);
    }
}

void UvuvMotor::spinUntilDegree(int degree, int speedInVoltage) {
    if (getEncoderPos() < degree) {
        spinAtVoltage(speedInVoltage);
    }
    else {
        spinAtVoltage(0);
    }
}

void UvuvMotor::spinFor(float seconds, int speedInVoltage) {
    if (!isBroken) {
        static float startTime = pros::millis();

        if (pros::millis() - startTime < seconds * 1000) {
            spinAtVoltage(speedInVoltage);
        }
        else {
            spinAtVoltage(0);
        }
    }
    

}

void UvuvMotor::logMotorPerformance() {

}

void UvuvMotor::set_zero_position(int position) {
    motor->set_zero_position(position);
}

void UvuvMotor::shutDown() {
    isBroken = true;
}

void UvuvMotor::revive() {
    isBroken = false;
}

bool UvuvMotor::isOverheated() {
    if (motor->get_temperature() > overheatTempCelsius) {
        return true;
    }
    else {
        return false;
    }
}