#pragma once

#include "Definitions.h"
#include "Motor.h"
#include "PID.h"

#include "unordered_map"
#include <unordered_map>

class UvuvFlywheelController { // Controls the flywheel's speed.
protected:

	int outputVoltage; // The voltage that the flywheel is outputting, from -12000 to 12000.
	float wheelDiameter; // The diameter of whatever wheel the flywheels are on, in inches.

    UvuvMotorGroup* uvuvMotors; // The Uvuv motor/motors used in the flywheel.

	static PIDFFController pidController; // The PID Controller that controls the flywheel.
	
    static std::vector<float> filteredPIDValues; // The filtered values of the flywheel output (RPM).

    Gearing flywheelGearing;
    /**
     * @brief Updates the PID Filter to be the average of the 6 motor values in the past 120 ms.
     * 
     */
	void updateFilter();

public:
	
	double targetRPM = 0;
	
	bool runBangBang = true; // Whether or not you want to run the Bang Bang algorithim on the flywheel.

    /**
     * @brief Construct a new Uvuv Flywheel Controller object.
     * 
     * @param motorArg Pointers to the Uvuv Motors used in the flywheel. If only one, still use the motor group data type.
     * @param wheelDiameterArg Diameter of the wheel in the flywheel, in inches.
     * @param pidArg A PID Controller to use in
     */
    UvuvFlywheelController(UvuvMotorGroup* motorArg, Gearing flywheelGearingArg, float wheelDiameterArg, 
        PIDFFController pidFFArg);
    
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
     * @brief Set the constants for the PID loop. In this case, its setting kP, kI, and kD.
     * 
     * @param kPArg 
     * @param kIArg 
     * @param kDArg 
     * @param kVArg
     */
    void setConstants(float kPArg, float kIArg, float kDArg, float kVArg);
	
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