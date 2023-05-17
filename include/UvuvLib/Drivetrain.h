#pragma once
#include "main.h"
#include "MotorGroup.h"

class UvuvDrivetrain {
private:
    
    uint8_t jerkControlSensitivityScale = 1; // 0 - 9, 0 being no control and 9 being very strong control

    static float inchesDriven;

	static float degreesTurned;

	int leftSideVoltage = 0;

	int rightSideVoltage = 0; 

    uint8_t percisionPercentage = 100;

    UvuvMotorGroup* driveLeftSide;
    UvuvMotorGroup* driveRightSide;

    bool hasJerkControl = false;
    bool hasActiveBraking = false; 
    bool isReversed = false;
	bool areFrontMotorsShutDown = false;
	bool areBackMotorsShutDown = false;
	bool isDriver;
	bool isPercision = false;

protected:

	UvuvDrivetrain();

public:

	/**
	 * @brief Construct a new Uvuv Drivetrain object
	 * 
	 * @param leftSidePtr Pointer to the left side motor group
	 * @param rightSidePtr Pointer to the right side motor group
	 */
	UvuvDrivetrain(UvuvMotorGroup* leftSidePtr, UvuvMotorGroup* rightSidePtr);

	/**
	 * @brief Construct a new Uvuv Drivetrain object
	 * 
	 * @param motorParameters The port number and then the rotation direction of the motor
	 */
	UvuvDrivetrain(std::vector<std::pair<int, motorRotation>> motorParameters);

	/*------------------------------------------------------------*/

	int driveTrainPercentage();

	/*------------------------------------------------------------*/

	void driveStop();

	/*------------------------------------------------------------*/

	void takeControllerInput(pros::Controller Controller1);

	/*------------------------------------------------------------*/
    
    void evaluatePercision();

	/*------------------------------------------------------------*/

	void evaluateReverse();

	/*------------------------------------------------------------*/

	void spinMotors();

	/*------------------------------------------------------------*/

	void driveTrainMainLoop();
	
	/*------------------------------------------------------------*/

	void setVoltages(int rightVoltage, int leftVoltage);

	/*------------------------------------------------------------*/

	void driveTo(float inches);

	/*------------------------------------------------------------*/

	void turnTo(float degrees);

	/*------------------------------------------------------------*/

	void turnAndDriveTo(float inches, float degrees);

	/*------------------------------------------------------------*/

};
