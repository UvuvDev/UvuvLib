#pragma once

#include "Motor.h"
#include "main.h"

#include "Definitions.h"
#include "PID.h"
#include "MotorGroup.h"
#include "PTO.h"


class UvuvBasicLift {
private:

protected:

    PTO* pto;
    UvuvMotorGroup* liftMotors;
    PIDFFController* pidController;

    bool keepInPlace = false;

    UvuvBasicLift();

public:   

    UvuvBasicLift(UvuvMotorGroup* liftMotorsArg, int lengthOfArmArg, PIDFFController* pidFFControllerArg);

    void rotateLiftTo(float degrees);

};

class UvuvAdvancedLiftParentClass : public UvuvBasicLift{
private: 

protected:

    float lengthOfArm = 0; // SPECIFY IN INCHES
    float minimumHeight = 0; // SPECIFY IN INCHES
    float maximumHeight = 0;
    int gamepiecesHeld = 0;

    bool isHoldingPiece = false; 

    UvuvAdvancedLiftParentClass();

public:

    /**
     * @brief Construct a new Uvuv Lift System
     * 
     * @param liftMotorsArg Pointer to an UvuvMotorGroup object
     * @param lengthOfArmArg Length of arm IN INCHES
     * @param pidControllerArg Pointer to a PID Feed Forward Controller
     */
    UvuvAdvancedLiftParentClass(UvuvMotorGroup* liftMotorsArg, float lengthOfArmArg, PIDFFController* pidFFControllerArg, float inchesFromGround,
    float minimumHeightArg, float maximumHeightArg);

    /**
     * @brief Construct a new Uvuv Lift System
     * 
     * @param motorParameters An std::pair with the port number and motor rotation
     * @param lengthOfArmArg Length of arm IN INCHES.
     * @param pidControllerArg Pointer to a PID Feed Forward Controller
     */
    UvuvAdvancedLiftParentClass(std::vector<std::pair<int, motorRotation>> motorParameters, float lengthOfArmArg, 
        PIDFFController* pidControllerArg, float minimumHeightArg, float maximumHeightArg);

    /**
     * @brief Keeps the lift at a constant height. First rotates to the correct height from the ground, then keeps it there.
     * 
     * @param inchesFromGround 
     */
    void keepConstantHeight(float inchesFromGround);  

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

