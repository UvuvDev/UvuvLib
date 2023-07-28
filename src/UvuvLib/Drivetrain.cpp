
#include "UvuvLib/Drivetrain.h"
#include "Definitions.h"
#include "UvuvController.h"
#include "UvuvLib/Math.h"
#include "pros/misc.h"







float UvuvDrivetrain::inchesDriven;
float UvuvDrivetrain::degreesTurned; 


UvuvDrivetrain::UvuvDrivetrain(UvuvMotorGroup* leftSidePtr, UvuvMotorGroup* rightSidePtr, Gearing gearingArg, float wheelSizeArg,
	UvuvBasicController* controllerArg, pros::IMU* inertialSensorArg, ControlScheme controlSchemeArg) {
	
	driveLeftSide = leftSidePtr;
	driveRightSide = rightSidePtr;		

	dtGearing = gearingArg;
	wheelSize = wheelSizeArg;
	uvuvControllerPtr = controllerArg;

	inertialSensor = inertialSensorArg;
	
	inchesDriven = 0;

	filteredLeftVolt.resize(4);
	filteredRightVolt.resize(4);

	controlScheme = controlSchemeArg;

	
}

UvuvDrivetrain::UvuvDrivetrain(std::vector<std::pair<int, motorRotation>> motorLeftParameters, 
	std::vector<std::pair<int, motorRotation>> motorRightParameters, Gearing gearingArg, float wheelSizeArg,
		UvuvBasicController* controllerArg, pros::IMU* inertialSensorArg, ControlScheme controlSchemeArg) {
			
    driveLeftSide = new UvuvMotorGroup(motorLeftParameters);    
    driveRightSide = new UvuvMotorGroup(motorRightParameters);

	dtGearing = gearingArg;
	wheelSize = wheelSizeArg;
	uvuvControllerPtr = controllerArg;

	inchesDriven = 0;

	inertialSensor = inertialSensorArg;

	filteredLeftVolt.resize(4);
	filteredRightVolt.resize(4);

	controlScheme = controlSchemeArg;


}

void UvuvDrivetrain::driveStop() {
	leftSideVoltage = 0;
	rightSideVoltage = 0;

}
void UvuvDrivetrain::takeControllerInput(UvuvBasicController* controllerArg) {

	if (controlScheme == ControlScheme::E_ARCADE_DRIVE) {
		leftSideVoltage = controllerArg->getJoystick(pros::E_CONTROLLER_ANALOG_LEFT_Y) + 
			controllerArg->getJoystick(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	
		rightSideVoltage = controllerArg->getJoystick(pros::E_CONTROLLER_ANALOG_LEFT_Y) - 
			controllerArg->getJoystick(pros::E_CONTROLLER_ANALOG_RIGHT_X);
	}
	else if (controlScheme == ControlScheme::E_TANK_DRIVE) {
		leftSideVoltage = controllerArg->getJoystick(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	
		rightSideVoltage = controllerArg->getJoystick(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	}
	else {
		leftSideVoltage = controllerArg->getJoystick(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	
		rightSideVoltage = controllerArg->getJoystick(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
	}

	
	
}
void UvuvDrivetrain::evaluatePercision() {
	
	if (isPercision == true) {
		leftSideVoltage = leftSideVoltage * percisionPercentage / 100;
		rightSideVoltage = rightSideVoltage * percisionPercentage / 100;
	}
	
}
void UvuvDrivetrain::evaluateReverse() {
	
	if (isReversed == true) {
		leftSideVoltage *= -1;
		rightSideVoltage *= -1;
	}
	
}
void UvuvDrivetrain::spinMotors() {
	driveLeftSide->spinAtVoltage(leftSideVoltage);
	driveRightSide->spinAtVoltage(rightSideVoltage);
}
void UvuvDrivetrain::driveTrainMainLoop() {
	
	if (isDriver) {
		takeControllerInput(uvuvControllerPtr);
	}
	
	evaluatePercision();
	evaluateReverse();
	spinMotors();
}

void UvuvDrivetrain::setVoltages(int rightVoltage, int leftVoltage) {
	leftSideVoltage = leftVoltage;
	rightSideVoltage = rightVoltage;
}

void UvuvDrivetrain::driveTo(float inches) {	
	// Graphing stuff	
	graphy::AsyncGrapher GraphTool("Drivetrain Oscillation"); 

	GraphTool.addDataType("Target", COLOR_HOT_PINK);
	
	GraphTool.addDataType("Actual", COLOR_AQUA);
	
	GraphTool.startTask();		
	
	// Make sure the encoder ticks on the drive are 0
	driveLeftSide->set_zero_position(0);
	driveRightSide->set_zero_position(0);
	
	inchesDriven = 0;
	static uint32_t driveTick = 0;
	driveTick = 0;
	float requestedInches = inches;
	int timeSinceErrorZero = 0;
	bool startTimer = false;
	bool runPID = true;

	while (runPID) { // requestedInches - inchesDriven > .02 
		
		std::vector<double> driveVector = { driveRightSide->getAverageEncoderPositions() }; // Average the right side encoders
		
		inchesDriven = averageNumbers(driveVector) / dtGearing * wheelSize * pi; // Convert the ticks into inches
		
		std::cout << "Inches driven: " << inchesDriven << std::endl; // Print inches driven to the terminal
		
		int leftVoltage = driveLeftSide->getDrivePID()->step(inchesDriven, requestedInches); // PID Step
		int rightVoltage = driveRightSide->getDrivePID()->step(inchesDriven, requestedInches); // PID Step

		// Move drivetrain
		driveLeftSide->spinAtVoltage(leftVoltage);
		driveRightSide->spinAtVoltage(rightVoltage);
		
		// Graphing stuff
		GraphTool.update("Target", 
			static_cast<float>( requestedInches / (requestedInches*2) ));
		GraphTool.update("Actual", 
			static_cast<float>( inchesDriven / (requestedInches*2) ));
		driveTick++;
		
		// Exit conditions:
		if (driveLeftSide->getAverageRPM() < 5 && driveRightSide->getAverageRPM() < 5) {
			startTimer = true; // If the left side is slower than 5 RPM, start a timer 
		
		}
		if (startTimer) {
			timeSinceErrorZero++; // If the timer is actually on, add one to timeSinceErrorZero
		}
		
		// If error is within .1 and also timeSinceErrorZero variable is > 70 (1.4 seconds in actual time)
		if (inchesDriven < requestedInches + .1 && inchesDriven > requestedInches - .1 && timeSinceErrorZero > 70.f) {
			runPID = false;
			GraphTool.pauseTask();
			break;
		}
  }
	GraphTool.pauseTask();
	//GraphTool.stopTask();
	driveLeftSide->spinAtVoltage(0);
	driveRightSide->spinAtVoltage(0);
	
	inchesDriven = 0;
	
}	
	

	
void UvuvDrivetrain::turnTo(float degrees) {
	
	graphy::AsyncGrapher GraphTool("Drivetrain Oscillation");

	GraphTool.addDataType("Target", COLOR_HOT_PINK);
	
	GraphTool.addDataType("Actual", COLOR_AQUA);
	GraphTool.addDataType("Voltage", COLOR_GOLD);
	
	GraphTool.startTask();

	uint32_t driveTick = 0;
	driveTick = 0;
	int degreesAtStart = inertialSensor->get_rotation();
	int millisSinceStart = pros::millis();
	int timeSinceErrorZero = 0;
	bool startTimer = false;
	bool runPID = true;

	while (runPID) { // requestedInches - inchesDriven > .02 
		
		int leftVoltage = driveLeftSide->getTurnPID()->step(inertialSensor->get_rotation(), degreesAtStart + degrees);
		int rightVoltage = driveRightSide->getTurnPID()->step(inertialSensor->get_rotation(), degreesAtStart + degrees);

		std::cout << "Yaw: " << inertialSensor->get_rotation() << std::endl;
		driveLeftSide->spinAtVoltage(leftVoltage);
		driveRightSide->spinAtVoltage(-rightVoltage);
		GraphTool.update("Target", 
			static_cast<float>( degrees / (degrees*2) ));
		GraphTool.update("Actual", 
			static_cast<float>( inertialSensor->get_rotation() - degreesAtStart / (degrees*2)));
		GraphTool.update("Voltage", 
			static_cast<float>( (float)leftVoltage / 12000 ));
		driveTick++;
		
		if (driveRightSide->getAverageRPM() < .2 && driveLeftSide->getAverageRPM() < .2) {
			startTimer = true;
		
		}
		if (timeSinceErrorZero == 0 && startTimer) {
			timeSinceErrorZero = pros::millis();
		}
		if ((inertialSensor->get_rotation() < degreesAtStart + degrees + .6 && inertialSensor->get_rotation() > 
				degreesAtStart + degrees - .6 && pros::millis() - timeSinceErrorZero > 400.f) || 
				pros::millis() - millisSinceStart > 3000) {
			
			runPID = false;
			GraphTool.pauseTask();
			break;
		}

		pros::delay(20);
		
  }
	GraphTool.pauseTask();
	//GraphTool.stopTask();
	inchesDriven = 0;
}
	

void UvuvDrivetrain::turnAndDriveTo( float inches, float degrees) {
	inchesDriven = 0;
	degreesTurned = 0;
	static uint32_t driveTick = 0;
	driveTick = 0;

	int degreesAtStart = inertialSensor->get_rotation();

	while (inches - inchesDriven < .1 && inches - inchesDriven > -.1) {

		// Turn
		std::vector<double> turnVector = { driveLeftSide->getAverageRPM(), driveRightSide->getAverageRPM() };
		degreesTurned += averageNumbers(turnVector) * dtGearing;				
		
		int turnVoltage = driveLeftSide->getTurnPID()->step(degreesTurned, degrees);
		
		// Drive
		
		std::vector<double> driveVector = { driveLeftSide->getAverageRPM(), driveRightSide->getAverageRPM() };
		inchesDriven += averageNumbers(driveVector) * dtGearing * wheelSize * pi / 1000;
		
		int leftVoltage = driveLeftSide->getDrivePID()->step(inchesDriven, inches);
		int rightVoltage = driveRightSide->getDrivePID()->step(inchesDriven, inches);
		
		driveLeftSide->spinAtVoltage(leftVoltage - turnVoltage);
		driveRightSide->spinAtVoltage(rightVoltage + turnVoltage);
		driveTick++;

		while (pros::c::millis() < (uint32_t)60 * driveTick) {

		}

    }

	inchesDriven = 0;
	degreesTurned = 0;

}

