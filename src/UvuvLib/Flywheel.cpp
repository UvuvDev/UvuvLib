#include "UvuvLib/Flywheel.h"
#include "UvuvLib/Math.h"
#include "UvuvLib/GraphingTool.h"

PIDController UvuvFlywheelController::pidController(0);

std::vector<float> UvuvFlywheelController::filteredPIDValues = {0};

UvuvFlywheelController::UvuvFlywheelController(UvuvMotorGroup* motorArg, Gearing flywheelGearingArg, float wheelDiameterArg, 
	float kPArg, float kIArg, float kDArg) {
	
	kP = kPArg;
	kI = kIArg;
	kD = kDArg;

	uvuvMotors = motorArg;
	flywheelGearing = flywheelGearingArg;

	wheelDiameter = wheelDiameterArg;

}

void UvuvFlywheelController::setConstants(float kVArg) {
	kV = kVArg;
}
void UvuvFlywheelController::setConstants(float kPArg, float kIArg, float kDArg) {
	kP = kPArg;
	kI = kIArg;
	kD = kDArg;
	pidController.kP = kPArg;
	pidController.kI = kIArg;
	pidController.kD = kDArg;
}
void UvuvFlywheelController::step() {
	//std::cout << "kVvalues: " << kVvalues[targetRPM].kV << "\n";
	if (uvuvMotors->getAverageRPM() < targetRPM - 650 && runBangBang) {
		
		uvuvMotors->spinAtVoltage(10500);
		updateFilter();
	
	}
	
	else { 
		
		//pidControl.kV = kV; // Set PID kV to the controllers kV, <3 classes initalizing
		updateFilter();

		float PIDAverage = averageNumbers(filteredPIDValues);

		int outputVoltage = pidController.step(PIDAverage, targetRPM);
		if (kV + outputVoltage < 0) {
			outputVoltage = 0;
		}
		
		uvuvMotors->spinAtVoltage(outputVoltage + kV);
		
	
	}
	
	
}
void UvuvFlywheelController::startFlywheelControlTask() {
	pros::Task task{[=] {
		graphy::AsyncGrapher GraphTool("Flywheel Velocity");

		GraphTool.addDataType("Target", COLOR_HOT_PINK);
	
		GraphTool.addDataType("Actual", COLOR_AQUA);
		GraphTool.addDataType("Actual Filtered", COLOR_GOLD);
	
		GraphTool.startTask();
		
		while (1) {
			
			GraphTool.update("Actual", 
				static_cast<float>(uvuvMotors->getAverageRPM())
				/ (3600.f));
			GraphTool.update("Actual Filtered", getFilteredPIDOutput() / 3600.f);
	
			GraphTool.update("Target", targetRPM / 3600.f); // metaUvuvFlywheelController.targetRPM
			
			/*
			GraphTool.zoomUpdate("Target", targetRPM, 
				{targetRPM - 2000, targetRPM + 2000}, GEARING_DIRECT_INSERT);
			GraphTool.zoomUpdate("Actual", 
				static_cast<float>(Math::getRPM(flywheelGroupPtr, GEARING_DIRECT_INSERT)), 
				{targetRPM - 2000, targetRPM + 2000}, GEARING_DIRECT_INSERT);
			GraphTool.zoomUpdate("Actual Filtered", getFilteredPID(), 
				{targetRPM - 2000, targetRPM + 2000}, GEARING_DIRECT_INSERT);
			*/
			step();
			pros::delay(20);
		}
		
	}};
	
}
void UvuvFlywheelController::updateFilter() {

	std::rotate(begin(filteredPIDValues), end(filteredPIDValues) - 1, end(filteredPIDValues));
	//std::shift_left(begin(filteredPIDValues), end(filteredPIDValues), 1);
	filteredPIDValues.resize(filteredPIDValues.size() - 1);
	filteredPIDValues.emplace_back(uvuvMotors->getAverageRPM());

}
float UvuvFlywheelController::getFilteredPIDOutput() {
	return averageNumbers(filteredPIDValues);
}
void UvuvFlywheelController::stopFlywheel() {
	uvuvMotors->spinAtVoltage(0);
	setConstants(0);
	setConstants(0, 0, 0);
	
}
bool UvuvFlywheelController::getCanFire() {
	
	if (uvuvMotors->getAverageRPM() > targetRPM - 100) {
		return true;
	}
	else {
		return false;
	}
	
}