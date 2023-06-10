#pragma once

#include "MotorGroup.h"
#include "PID.h"

#include "unordered_map"
#include <unordered_map>

class UvuvFlywheelController { // Controls the flywheel's speed.
protected:

	int outputVoltage; // The voltage that the flywheel is outputting, from -12000 to 12000.
	float wheelDiameter; // The diameter of whatever wheel the flywheels are on, in inches.

	pros::MotorGroup* flyMotors; // The PROS motor/motors used in the flywheel.

    UvuvMotorGroup* uvuvMotors; // The Uvuv motor/motors used in the flywheel.

	static PIDController pidController; // The PID Controller that controls the flywheel.
	
    static std::vector<float> filteredPIDValues; // The filtered values of the flywheel output (RPM).

    /**
     * @brief Updates the PID Filter to be the average of the 6 motor values in the past 120 ms.
     * 
     */
	void updateFilter();

public:
	
	double targetRPM = 0;
	float kP;
	float kI;
	float kD;
	float kV;
	
	bool runBangBang = true; // Whether or not you want to run the Bang Bang algorithim on the flywheel.

    /**
     * @brief Construct a new Uvuv Flywheel Controller object.
     * 
     * @param motorArg Pointers to the PROS Motors used in the flywheel. If only one, still use the motor group data type.
     * @param wheelDiameterArg Diameter of the wheel in the flywheel, in inches.
     * @param kPArg Proportional constant for the PID loop.
     * @param kIArg Integral constant for the PID loop.
     * @param kDArg Derivative constant for the PID loop.
     */
	UvuvFlywheelController(pros::MotorGroup* motorArg, float wheelDiameterArg, float kPArg, float kIArg, float kDArg);

    /**
     * @brief Construct a new Uvuv Flywheel Controller object.
     * 
     * @param motorArg Pointers to the Uvuv Motors used in the flywheel. If only one, still use the motor group data type.
     * @param wheelDiameterArg Diameter of the wheel in the flywheel, in inches.
     * @param kPArg Proportional constant for the PID loop.
     * @param kIArg Integral constant for the PID loop.
     * @param kDArg Derivative constant for the PID loop.
     */
    UvuvFlywheelController(UvuvMotorGroup* motorArg, float wheelDiameterArg, float kPArg, float kIArg, float kDArg);
    
    /**
     * @brief Updates the PID loop for the flywheel. !!! NOT A TASK !!!
     * 
     */
    void step(); 
    
    /**
     * @brief Creates a task that updates the PID loop for the flywheel, without needing to call step() every time.
     * !!! WARNING, DO NOT PUT INSIDE A LOOP. WILL CRASH THE V5 !!!
     */
    void startFlywheelControlTask();
	
    /**
     * @brief Sets the constants for the PID loop. In this case, its only setting kV.
     * 
     * @param kVArg 
     */
    void setConstants(float kVArg); 
	
    /**
     * @brief Set the constants for the PID loop. In this case, its setting kP, kI, and kD.
     * 
     * @param kPArg 
     * @param kIArg 
     * @param kDArg 
     */
    void setConstants(float kPArg, float kIArg, float kDArg);
	
    /**
     * @brief Get the Filtered PID output in RPM. Can be used for things like displaying the RPM on the brain.
     * 
     * @return float 
     */
    float getFilteredPIDOutput();
    
    /**
     * @brief An emergency shut down of the flywheel. Sets the output voltage to 0.
     * 
     */
    void stopFlywheel();
	
    /**
     * @brief Gets whether or not the flywheel can fire. 
     * 
     * @param input 
     */
    bool getCanFire();

};