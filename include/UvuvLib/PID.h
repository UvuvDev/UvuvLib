#pragma once

struct PIDConstants {

	float kP, kI, kD, kV;

	/**
	 * @brief Construct a new PIDConstants object with all 3 constants. 
	 * 
	 * @param kPParam kP Value
	 * @param kIParam kI Value
	 * @param kDParam kD Value
	 * @param kVParam kV Value, optional. Defaults to 0.
	 */
	PIDConstants(float kPParam, float kIParam, float kDParam, float kVParam = 0) : kP(kPParam), kI(kIParam), kD(kDParam), kV(kVParam){}

};

class PIDController { // Basic PID controller, can be used for literally anything you want.
protected:
		
	float targetRPM;

public:

    float kP; // Gets you close to the target RPM, but not all the way. The P (proportional) in PID. CANNOT be 0.
	float kI; // Gets you to exactly the target RPM. The I (Integral Constant) in PID.
	float kD; // Adds extra speed to the motors if there needs to be extra torque 
					// (like if you were holding a mogo, youd need extra force to keep it in place). The D (Derivative) in PID.
	float error = 0;
	float previous_error = 0;
	float integral = 0;
	float integral_threshold = 0;
	float derivative = 0;	

	PIDController();
		
	// Fix error where if kPparam is defaulted to 0 it throws an error
	PIDController (float kPParam, float kIParam = 0, float kDParam = 0, float integral_thresholdParam = 10, float kVParam = 0);

	int step(float actual, float target);

	
};

class PIDFFController : public PIDController { 	
protected:
	
public:

	float kV;
	float kG;
	float kS;
	float kA;

	/**
	 * @brief Construct a new PIDFeedForwardController object
	 * 
	 * @param kPParam Proportional, brings the RPM up most of the way.
	 * @param kIParam Integral, brings the RPM up the rest.
	 * @param kDParam Derivative, gets rid of any oscillation.
	 * @param kVParam Velocity, multiplies by RPM of motor.
	 * @param kAParam Acceleration, multiplies by acceleration.
	 * @param kGParam Gravity constant, for lifts ONLY.
	 * @param kSParam Static friction constant, makes the motor go the minimum voltage needed to spin.
	 * @param integral_thresholdParam 
	 */
	PIDFFController(float kPParam = 0, float kIParam = 0, float kDParam = 0, float kVParam = 0, float kAParam = 0, float kGParam = 0, float kSParam = 0, float integral_thresholdParam = 10);
		
	/**
	 * @brief Steps the PID forward, save the RPM if you want to send it to different motors.
	 * PID + FEED FORWARD
	 * @param flywheelMotorOne flywheelMotor you want to use
	 * @param targetRPM target RPM of the motor
	 * @return int
	 */
	
	int step(float actual, int targetRPM);

};