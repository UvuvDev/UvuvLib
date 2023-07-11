#include "UvuvLib/PID.h"
#include "UvuvLib/Math.h"

/*-----------------PIDController-----------------*/
	
	/*-------Initialization-------*/
	PIDController::PIDController() {
		// Pass
	}

	PIDController::PIDController (float kPParam, float kIParam, float kDParam, float integral_thresholdParam, float kVParam) {
			
		kP = kPParam;
		kI = kIParam;
		kD = kDParam;
		integral_threshold = integral_thresholdParam;
		// Remember to set controller target
	}
	
	/*-------Member Functions-------*/
	int PIDController::step(float actual, float target) {
	
		targetRPM = target;
	
		previous_error = error; // Save previous error
	
		error = targetRPM - actual; // Get error by doing targetSpeed - currentPos
	
		if (std::abs(error) < integral_threshold) { // Since abs is an int, it cant get too accurate, since error is a float. thats what I is for
			integral += error; // Add up errors to the integral.
		}
	
		else {
			integral = 0; // Reset the integral, so that way the integral doesnt get super huge once its over the threshold. 
		}
	
		derivative = error - previous_error; // Calculates derivative by subtracting the previous error from error
	
		return (kP * error) + (kI * integral) + (kD * derivative);

	}

/*-------------------------------------------------------------*/

/*-----------------PIDFFController-----------------*/
	PIDFFController::PIDFFController(float kPParam, float kIParam, float kDParam, float kVParam,  float kAParam, float kGParam, float kSParam, float integral_thresholdParam) {
		
		kP = kPParam;
		kI = kIParam;
		kD = kDParam;
		kV = kVParam;
		kG = kGParam;
		kS = kSParam;
		kA = kAParam; 
		integral_threshold = integral_thresholdParam;

	}

	int PIDFFController::step(float actual, int target) {
		
		targetRPM = target;
		
		previous_error = error; // Save previous error
		
		error = targetRPM - actual; // Get error by doing targetSpeed - currentPos
		
		if (std::abs(error) < integral_threshold) { // Since abs is an int, it cant get too accurate, since error is a float. thats what I is for
			integral += error; // Add up errors to the integral.
		}
		
		else {
		integral = 0; // Reset the integral, so that way the integral doesnt get super huge once its over the threshold. 
		}
		
		derivative = error - previous_error; // Calculates derivative by subtracting the previous error from error
		
		int PIDOutput = (kP * error) + (kI * integral) + (kD * derivative);
		
		int FeedForwardOutput =  ( kG ) + (kS * signum(targetRPM)) + ( kV ) * ( targetRPM + kA );//*a; ADD ACCELERATION
	
		return PIDOutput + FeedForwardOutput;
		
	}

/*------------------------------------------------------------*/
