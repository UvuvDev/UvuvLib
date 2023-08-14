#pragma once

#include "Drivetrain.h"
#include "PID.h"
#include "Motor.h"
#include "Definitions.h"
#include "Math.h"

#define INVALID_POINT 852738

typedef std::vector<std::pair<float, float>> Path;

class PurePursuit {
private:

	UvuvDrivetrain* drivetrain;

	float maxVelocityInchesPerSecond;

	float lookaheadDistance;

	int lastPointPassed;

	std::vector<std::pair<float, float>> path;

	std::pair<float, float> goalPointCoords(std::pair<float, float> currentPos, std::vector<std::pair<float, float>> fullPath);

public:

	/**
	 * @brief Construct a new Pure Pursuit object
	 * 
	 * @param path Full Path in std::pairs. In inches!
	 * @param drivetrain Drivetrain
	 * @param lookaheadDistance The lookahead distance for the Pure Pursuit. Lower values have more oscillations, but 
	 *	 higher values less accurate. In inches!
	 * @param maxVelocityInchesPerSecond Keeps the bot from going too fast. In inches per second, default is 30.
	 */
	PurePursuit (std::vector<std::pair<float, float>> path, UvuvDrivetrain* drivetrain, float lookaheadDistance, 
		float maxVelocityInchesPerSecond = 30);

	/**
	 * @brief Steps the Pure Pursuit algorithm. Call this in a loop.
	 * 
	 * @param currentPos Position of the bot relative to the center of the field. It's similar to the GPS coordinates just in inches
	 * instead of meters.
	 * @param headingInDegrees Current heading of the bot. In Degrees.
	 */
	void step(std::pair<float, float> currentPos, float headingInDegrees);


};
