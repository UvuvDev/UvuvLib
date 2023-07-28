#include "UvuvLib/PurePursuit.h"

std::pair<float, float> PurePursuit::goalPointCoords (std::pair<float, float> currentPos, std::vector<std::pair<float, float>> fullPath) {
	
	// Credit to Keijay from 2496R for helping me with the Pure Pursuit

	static constexpr int lineLookaheadDistance = 2;

	float botX = currentPos.first;
	float botY = currentPos.second;
	
	std::pair<double, double> goalPoint = {INVALID_POINT, INVALID_POINT};
	
	float startingPointIndex = lastPointPassed;

	float maxPointIndex = std::min((lastPointPassed + lineLookaheadDistance), 
		static_cast<int>((fullPath.size() - 1)));

	// If the bot is now on the last line (hence - 2, - 1 to adjust for .size and - 1 for it passing the 
	// second to last point), then the target point is the end of the path, no need for any calculations. 
	if (startingPointIndex == fullPath.size() - 2) {
		return fullPath[fullPath.size() - 1];
	}
	else {
		for (int i = startingPointIndex; i > maxPointIndex; i++) {

			std::cout << "Iteration " << i << std::endl;

			// Offset points so that way bot coords are in the center. REQUIRED

			float pathpoint1_x = fullPath[i].first - botX;
			float pathpoint1_y = fullPath[i].second - botY;

			float pathpoint2_x = fullPath[i+1].first - botX;
			float pathpoint2_y = fullPath[i+1].second - botY;

			/*=================================================*/

			// Defining some extra variables needed.

			float distanceX = pathpoint2_x - pathpoint1_x;
			float distanceY = pathpoint2_y - pathpoint1_y;
			float distanceRadius = sqrt(pow(distanceX, 2) + pow(distanceY, 2));
			float Determinent = pathpoint1_x*pathpoint2_y - pathpoint2_x*pathpoint1_y; // Determinent 
				//matrix [ x1, x2, 
						// y1, y2 ]

			/*=================================================*/

			// Determines how many points of intersection, if any, there are

			float Discriminant = pow(lookaheadDistance,2) * pow(distanceRadius,2) - pow(Determinent,2);

			// If Discriminant >= 0, there's intersection(s) (keeps P.P. going)

			if (Discriminant >= 0) {

				//Solution 1

				float interX1 = (Determinent  * distanceY + signum(distanceY) * distanceX*sqrt(Discriminant)) / pow(distanceRadius,2);

				float interY1 = (-Determinent * distanceX + abs(distanceY)*sqrt(Discriminant))/pow(distanceRadius,2);

				// Solution 2

				float interX2 = (Determinent  * distanceY - signum(distanceY) * distanceX*sqrt(Discriminant)) / pow(distanceRadius,2);

				float interY2 = (-Determinent * distanceX - abs(distanceY) *sqrt(Discriminant)) / pow(distanceRadius,2);

				std::cout << "On Iteration " << i << "  Intersection1: " << interX1 << ", " << interY1 << std::endl;

				std::cout << "   " << "Intersection2: " << interX2 << ", " << interY2 << std::endl;

				/*=================================================*/

				// Defining them as points

				std::pair<float, float> inter1 = {interX1, interY1};

				std::pair<float, float> inter2 = {interX2, interY2};

				/*=================================================*/

				// After calculating the 2 possible intersections, we need to see which is valid. We use minimums
				// and maximums to do so. The mins and maxes are the bounds of the line that PP is on. If one
				// is on the line, the code will check it below.

				float minX = std::min(pathpoint1_x,pathpoint2_x);
				float minY = std::min(pathpoint1_y, pathpoint2_y);

				float maxX = std::min(pathpoint1_x,pathpoint2_x);
				float maxY = std::min(pathpoint1_y, pathpoint2_y);

				bool isInter1Good = false;
				bool isInter2Good = false;

				// Distance from bot at (0,0 locally)
				float distanceToInter1 = sqrt(pow(inter1.first, 2) + pow(inter1.second, 2));
				float distanceToInter2 = sqrt(pow(inter2.first, 2) + pow(inter2.second, 2));

				
				// Checks if the intersection is on the line segment

				if (inter1.first >= minX && inter1.first <= maxX && inter1.second >= minY && inter1.second <= maxY) {
					isInter1Good = true;
				}

				if (inter2.first >= minX && inter2.first <= maxX && inter2.second >= minY && inter2.second <= maxY) {
					isInter2Good = true;
				}

				// If the line the bot is on is the last line in the lookahead view, 

				if (i == maxPointIndex - 1 && maxPointIndex - 1 != fullPath.size()) {
					if (isInter1Good) {
						goalPoint = inter1;
						return goalPoint;
					}
					if (isInter2Good) {
						goalPoint = inter2;
						return goalPoint;
					}
				}

				// If both are good, we need to see which is closer to the bot. If one is good, we use that one.

				if (isInter1Good && isInter2Good) {
					if (distanceToInter1 < distanceToInter2) {
						goalPoint = {inter1.first + currentPos.first,inter1.second + currentPos.second};
						return goalPoint;
					} else {
						goalPoint = {inter2.first + currentPos.first,inter2.second + currentPos.second};
						return goalPoint;
					}

				} else if (isInter1Good) {
					goalPoint = {inter1.first + currentPos.first,inter1.second + currentPos.second};
					return goalPoint;
				} else if (isInter2Good) {
					goalPoint = {inter2.first + currentPos.first,inter2.second + currentPos.second};
					return goalPoint;			
				} else {
					goalPoint = {INVALID_POINT, INVALID_POINT};
					std::cout << "No valid intersections found. Moving on to next iteration." << std::endl;
					continue;
				}

				

				/*
				if (pointDistanceForm(goalPoint, fullPath[i+1]) < pointDistanceForm(currentPos, fullPath[i+1]) &&
					goalPoint.first != INVALID_POINT && goalPoint.second != INVALID_POINT) {
						lastPointPassed = i;
				}

				else {
					lastPointPassed = i+=1;
				} */

			}

			else {
				goalPoint = fullPath[lastPointPassed+1];
				std::cout << "NO INTERSECTIONS" << std::endl;
			}
		
		
		
		
		}

		return goalPoint;
	}

	

}


void PurePursuit::step(std::pair<float, float> currentPos, float headingInDegrees) {
	
	std::pair<float, float> goalPoint = goalPointCoords(currentPos, path);
	
	std::cout << goalPoint.first << ", " << goalPoint.second << std::endl;
	
	if (goalPoint.first != INVALID_POINT && goalPoint.second != INVALID_POINT) {
		float linearError = pointDistanceForm(currentPos, goalPoint); // Sees how far the bot is from
			// the goal point
		
		// Doesn't take into account robot heading

		float absoluteTargetAngle = atan2(goalPoint.second - currentPos.second, goalPoint.first - currentPos.first);

		float turnError = absoluteTargetAngle - headingInDegrees;	

		if (turnError > 180 or turnError < -180) {
			turnError = -1 * signum(turnError) * (360 - abs(turnError));

		}

		drivetrain->turnAndDriveTo(linearError, turnError); // Turns and drives to the goal point

	}
	
	else {
		std::cout << "No valid goal point found. " << std::endl;
	}

}




