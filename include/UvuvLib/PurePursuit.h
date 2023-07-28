#pragma once

#include "Drivetrain.h"
#include "PID.h"
#include "Motor.h"
#include "Definitions.h"
#include "Math.h"

#define INVALID_POINT 852738

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
	 *	 higher values less accurate.
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

/*


func pointDistanceForm(pointA, pointB):
	return sqrt(pow((pointA[0]-pointB[0]),2) + pow((pointA[1]-pointB[1]),2))
	
	
func sgn(x):
	if (x < 0):
		return -1
	else:
		return 1	
	


func goalPointCoords (currentPos, fullPath, lookAheadDistance, lastPointPassed):
	
	var botX = currentPos[0]
	var botY = currentPos[1]
	
	var goalPoint = [ERROR_VALUE, ERROR_VALUE]
	
	var startingPointIndex = lastPointPassed
	
	for i in range(startingPointIndex, len(fullPath)-1):
		
		print("Iteration ", i)
		
		# Offset points so that way bot coords are in the center. REQUIRED
		var pathpoint1_x = fullPath[i][0] - botX
		var pathpoint1_y = fullPath[i][1] - botY
		
		var pathpoint2_x = fullPath[i+1][0] - botX
		var pathpoint2_y = fullPath[i+1][1] - botY
		# ----------------------------------- #
		
		# Defining some extra variables needed.
		var distanceX = pathpoint2_x - pathpoint1_x 
		var distanceY = pathpoint2_y - pathpoint1_y
		var distanceRadius = sqrt(pow(distanceX, 2) + pow(distanceY, 2))
		
		var Determinent = pathpoint1_x*pathpoint2_y - pathpoint2_x*pathpoint1_y # Determinent 
			#matrix [ x1, x2, 
					# y1, y2 ]
		
		# ----------------------------------- #
		
		
		# Determines how many points of intersection, if any, there are
		var Discriminant = pow(lookAheadDistance,2) * pow(distanceRadius,2) - pow(Determinent,2)
		
		# If Discriminant >= 0, there's intersection(s) (keeps P.P. going)
		if (Discriminant >= 0):
			
			#Solution 1
			var interX1 = (Determinent  * distanceY + sgn(distanceY) * distanceX*sqrt(Discriminant)) / pow(distanceRadius,2)
				
			var interY1 = (-Determinent * distanceX + abs(distanceY)*sqrt(Discriminant))/pow(distanceRadius,2)
			
			# Solution 2
			var interX2 = (Determinent  * distanceY - sgn(distanceY) * distanceX*sqrt(Discriminant)) / pow(distanceRadius,2)
				
			var interY2 = (-Determinent * distanceX - abs(distanceY) *sqrt(Discriminant)) / pow(distanceRadius,2)
			
			
			print("On Iteration ", i, "  Intersection1: ", interX1, ", ", interY1)
			print("   ", "Intersection2: ", interX2, ", ", interY2)
			
			# Defining them as points
			var inter1 = [interX1, interY1]
			var inter2 = [interX2, interY2]
			
			# After calculating the 2 possible intersections, we need to see which is valid. We use minimums
			# and maximums to do so. The mins and maxes are the bounds of the line that PP is on. If one
			# is on the line, the code will check it below.
			var minX = min(pathpoint1_x,pathpoint2_x) 
			var minY = min(pathpoint1_y, pathpoint2_y)
			
			var maxX = min(pathpoint1_x,pathpoint2_x) 
			var maxY = min(pathpoint1_y, pathpoint2_y)
			
			var isInter1Good = false
			var isInter2Good = false
			
			if (minX <= interX1 and interX1 <= maxX and minY <= interY1 and interY1 <= maxY):
				isInter1Good = true
				
			if (minX <= interX2 and interX2 <= maxX and minY <= interY2 and interY2 <= maxY):
				isInter2Good = true
			else: 
				goalPoint = [ERROR_VALUE, ERROR_VALUE]
				print("NONE IN RANGE")
			
			
			
			
			
			
			
			# Goal Point selection
			
			if (isInter1Good != isInter2Good):
				if (isInter1Good):
					# Reverse offsetting before returning
					goalPoint = [interX1 + botX, interY1 + botY]
					print("POINT FOUND: ", goalPoint)
				if (isInter2Good):
					# Reverse offsetting before returning
					goalPoint = [interX2 + botX, interY2 + botY]
					print("POINT FOUND: ", goalPoint)
			if (isInter1Good and isInter2Good):
				var inter1Distance2Pt = pointDistanceForm(inter1, [pathpoint2_x, pathpoint2_y])
				var inter2Distance2Pt = pointDistanceForm(inter2, [pathpoint2_x, pathpoint2_y])
			
				if (inter1Distance2Pt < inter2Distance2Pt): 
					# Reverse offsetting before returning
					goalPoint = [interX1 + botX, interY1 + botY]
					print("POINT FOUND: ", goalPoint)
				else:
					# Reverse offsetting before returning
					goalPoint = [interX2 + botX, interY2 + botY]
					print("POINT FOUND: ", goalPoint)
					
				
			# If the point is closer to the next point than the current bot position:
			if (pointDistanceForm(goalPoint, fullPath[i+1]) < pointDistanceForm(currentPos, fullPath[i+1])):
				# Writes over the lastPointPassed INPUTTED variable, then exits
				lastPointPassed = i
				print("Point is closer to next point than the bots pos. VALID")
				break
			else:
				# If the bot can't find a valid point, it sets the last point passed to +=1 so it
				# does not go backward
				lastPointPassed = i+1
				print("Bot is closer than any point. INVALID")
				
		else:
			goalPoint = fullPath[lastPointPassed+1]
			print("NO INTERSECTIONS")
			
	return goalPoint


func PurePursuitStep():
	
	var path = [[0,0], [12000,8000], [16000, 2000], [12000, -2000], [0, -4000], [-4000,8000]]
	
	var lastPointPassed = 0
	
	var kPLin = .12
	var kPTurn = .4
	
	var lookaheadDistance = 250
	
	var currentPos = [0,0]
	
	var goalPoint = goalPointCoords(coords, path, lookaheadDistance, lastPointPassed)
	
	print(goalPoint)
	
	if (goalPoint != [ERROR_VALUE, ERROR_VALUE]):
		var linearError = pointDistanceForm(currentPos, goalPoint) # Sees how far the bot is from
			# the goal point
			
		# Doesn't take into account robot heading
		var absoluteTargetAngle = atan2(goalPoint[1] - currentPos[1], goalPoint[0] - currentPos[0])
			
		var turnError = absoluteTargetAngle - rotation
			
		if (turnError > 180 or turnError < -180):
			turnError = -1 * sgn(turnError) * (360 - abs(turnError))
		
		turnError *= kPTurn
		linearError *= kPLin
		
		return [turnError, linearError]
	else:
		return [0,0]


 */