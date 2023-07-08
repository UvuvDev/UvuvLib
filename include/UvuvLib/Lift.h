#pragma once

#include "Motor.h"
#include "main.h"

#include "Definitions.h"
#include "PID.h"
#include "PTO.h"


class UvuvBasicLift {
private:

protected:

    PTO* pto;
    UvuvMotorGroup* liftMotors;
    PIDFFController* pidController;

    bool keepInPlace = true;

    UvuvBasicLift();

public:   

    /**
     * @brief Construct a new Uvuv Basic Lift object
     * 
     * @param liftMotorsArg The motor group for the Lift Motors
     * @param pidFFControllerArg Can be a PIDController or PIDFFController
     * @param ptoArg Optional pointer to a PTO. Defaults to nullptr.
     */
    UvuvBasicLift(UvuvMotorGroup* liftMotorsArg, PIDFFController* pidFFControllerArg, PTO* ptoArg = nullptr);

    /**
     * @brief Rotates the lift to a specified degree
     * 
     * @param degrees 
     */
    void rotateLiftTo(float degrees);

    /**
     * @brief Rotates the lift by a specified voltage. 
     * 
     * @param voltage -128 to 127 range.
     */
    void rotateLiftByVoltage(float voltage);

    /**
     * @brief Turns the PTO on or off
     * 
     * @param state 
     */
    void setPTO(bool state);

};

class UvuvAdvancedLift : public UvuvBasicLift{
private: 

protected:

    float minimumHeight = 0; // SPECIFY IN INCHES
    float maximumHeight = 0;
    int gamepiecesHeld = 0;

    bool isHoldingPiece = false; 

public:

    /**
     * @brief Construct a new Uvuv Lift System
     * 
     * @param liftMotorsArg Pointer to an UvuvMotorGroup object
     * @param pidControllerArg Pointer to a PID Feed Forward Controller
     * @param defaultInchesFromGround Default height of the lift from the ground. IN INCHES
     * @param minimumHeightArg Minimum height of the lift from the ground. IN INCHES
     * @param maximumHeightArg Maximum height of the lift from the ground. IN INCHES
     */
    UvuvAdvancedLift(UvuvMotorGroup* liftMotorsArg, PIDFFController* pidFFControllerArg, float defaultInchesFromGround,
    float minimumHeightArg, float maximumHeightArg);

    /**
     * @brief Construct a new Uvuv Lift System
     * 
     * @param liftMotorsArg The port number and then the rotation direction of the lift motors
     * @param pidControllerArg Pointer to a PID Feed Forward Controller
     * @param defaultInchesFromGround Default height of the lift from the ground. IN INCHES
     * @param minimumHeightArg Minimum height of the lift from the ground. IN INCHES
     * @param maximumHeightArg Maximum height of the lift from the ground. IN INCHES
     */
    UvuvAdvancedLift(std::vector<std::pair<int, motorRotation>> motorParameters, 
        PIDFFController* pidFFControllerArg, float defaultInchesFromGround, float minimumHeightArg, float maximumHeightArg);

    /**
     * @brief Moves the lift to the maximum height possible.
     * 
     */
    void moveToMaxHeight();

    /**
     * @brief Moves the lift to the minimum height possible.
     * 
     */
    void moveToMinimumHeight();

    /**
     * @brief Move to any height specified. 
     * 
     * @param inchesFromGround 
     */
    void moveToHeight(float inchesFromGround);

    /**
     * @brief Get the number of gamepieces Being Held. Not useful for driver, but useful for auton.
     * 
     * @return int 
     */
    int getGamepiecesBeingHeld();

    /**
     * @brief Add 1 to the number of gamepieces being held. Not useful for driver, but useful for auton.
     * 
     * @param count 
     */
    void grabGamepiece(int count); 

    /**
     * @brief Subtract 1 from the number of gamepieces being held. Not useful for driver, but useful for auton.
     * 
     * @param count 
     */
    void dropGamepiece(int count); 

   

};

