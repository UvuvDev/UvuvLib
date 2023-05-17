#pragma once

#include "Motor.h"
#include "main.h"

#include "Definitions.h"
#include "PID.h"
#include "MotorGroup.h"

class UvuvLift {
private: //p

protected:

    UvuvMotorGroup* liftMotors;
    PIDFFController* pidController;

    float lengthOfArm = 0; // SPECIFY IN INCHES

    bool isHoldingPiece = false;
    bool keepInPlace = false;


public:

    /**
     * @brief Construct a new Uvuv Lift System
     * 
     * @param liftMotorsArg Pointer to an UvuvMotorGroup object
     * @param lengthOfArmArg Length of arm IN INCHES
     * @param pidControllerArg Pointer to a PID Feed Forward Controller
     */
    UvuvLift(UvuvMotorGroup* liftMotorsArg, int lengthOfArmArg, PIDFFController* pidFFControllerArg);

    /**
     * @brief Construct a new Uvuv Lift System
     * 
     * @param motorParameters An std::pair with the port number and motor rotation
     * @param lengthOfArmArg Length of arm IN INCHES
     * @param pidControllerArg Pointer to a PID Feed Forward Controller
     */
    UvuvLift(std::vector<std::pair<int, motorRotation>> motorParameters, int lengthOfArmArg, 
        PIDFFController* pidControllerArg);

    void keepConstantHeight(float inchesFromGround);

    void moveToMaxHeight();

    void moveToMinimumHeight();

    bool getIsHoldingObject();

    void objectGrabbed(); // Says that the lift is now holding an object

    void objectDropped(); // Says that the lift dropped the object

    void moveToHeight(float inchesFromGround);

};
