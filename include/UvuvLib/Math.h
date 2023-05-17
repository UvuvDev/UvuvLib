#pragma once

#include "main.h"
#include <math.h>

#include "Definitions.h"

/*------------------------------------------------------------*/

double averageNumbers(std::vector<double> numbersToAverage);

/*------------------------------------------------------------*/

float averageNumbers(std::vector<float> numbersToAverage);

/*------------------------------------------------------------*/

int averageNumbers(std::vector<int> numbersToAverage);

/*------------------------------------------------------------*/

bool isInRange(int16_t number, int16_t lower, int16_t higher);

/*------------------------------------------------------------*/

int16_t conv8b12000(float eightBitInt); // Converts a -128 - 127 range to -12000 - 12000

/*------------------------------------------------------------*/

int16_t conv12000to8b(float num12000); // Converts a -12000 - 12000 range to -128 - 127

/*------------------------------------------------------------*/

int8_t conv100to127(float tensNumber); // Converts 0 - 100 to 0 - 127

/*------------------------------------------------------------*/

int8_t conv127to100(float tensNumber); // Converts 0 - 127 to 0 - 100

/*------------------------------------------------------------*/

float convertInchesToDegrees(float inches, float wheelDiameter); 

/*------------------------------------------------------------*/

float convertDegreesToInches(float rotations, float wheelDiameter);



/*------------------------------------------------------------*/

uint8_t signum(double x);

/*------------------------------------------------------------*/

int getRPM(pros::Motor motor, Gearing gearing);

/*------------------------------------------------------------*/

int getRPM(pros::Motor* motor, Gearing gearing);

/*------------------------------------------------------------*/

int getRPM(pros::MotorGroup* motor, Gearing gearing);

/*------------------------------------------------------------*/

