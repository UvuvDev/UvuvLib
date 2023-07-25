#pragma once
#include "Definitions.h"
#include "main.h"
#include "Motor.h"
#include "PID.h"
#include "UvuvController.h"
#include "GraphingTool.h"
#include "pros/misc.hpp"

class UvuvDrivetrain {
private:
    
    uint8_t jerkControlSensitivityScale = 1; // 0 - 9, 0 being no control and 9 being very strong control

    static float inchesDriven;

	static float degreesTurned;

	int leftSideVoltage = 0;

	int rightSideVoltage = 0; 

	std::vector<int> filteredLeftVolt = {0, 0, 0, 0};

	std::vector<int> filteredRightVolt = {0, 0, 0, 0};

    uint8_t percisionPercentage = 100;

    UvuvMotorGroup* driveLeftSide;
    UvuvMotorGroup* driveRightSide;

	UvuvBasicController* uvuvControllerPtr;
	pros::Controller* prosControllerPtr;

	Gearing dtGearing;

	ControlScheme controlScheme;

	float wheelSize;

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
	 * @param gearingArg The gearing of the drivetrain
	 * @param wheelSizeArg The size of the wheels IN INCHES
	 * @param controllerPtr Pointer to your UvuvController
	 * @param controlSchemeArg The control scheme of the drivetrain. Accessed via ControlScheme::"Scheme Name"
	 */
	UvuvDrivetrain(UvuvMotorGroup* leftSidePtr, UvuvMotorGroup* rightSidePtr, Gearing gearingArg, float wheelSizeArg,
		UvuvBasicController* controllerArg, ControlScheme controlSchemeArg);

	/**
	 * @brief Construct a new Uvuv Drivetrain object
	 * 
	 * @param motorLeftParameters The port number and then the rotation direction of the left motors
	 * @param motorRightParameters The port number and then the rotation direction of the right motors
	 * @param gearingArg The gearing of the drivetrain
	 * @param wheelSizeArg The size of the wheels IN INCHES 
	 * @param controllerPtr Pointer to your UvuvController 
	 * @param controlSchemeArg The control scheme of the drivetrain. Accessed via ControlScheme::"Scheme Name"
	 */

	UvuvDrivetrain(std::vector<std::pair<int, motorRotation>> motorLeftParameters, 
		std::vector<std::pair<int, motorRotation>> motorRightParameters, Gearing gearingArg, float wheelSizeArg,
		UvuvBasicController* controllerArg, ControlScheme controlSchemeArg);

	/*------------------------------------------------------------*/

	void driveStop();

	/*------------------------------------------------------------*/

	void takeControllerInput(UvuvBasicController* controllerPtr);

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

	void turnTo(pros::IMU inertialSensor, float degrees);

	/*------------------------------------------------------------*/

	void turnAndDriveTo(pros::IMU inertialSensor, float inches, float degrees);

	/*------------------------------------------------------------*/

};
