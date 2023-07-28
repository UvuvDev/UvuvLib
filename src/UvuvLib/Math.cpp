
#include "UvuvLib/Math.h"

	/*------------------------------------------------------------*/

double averageNumbers(std::vector<double> numbersToAverage) {
	double sumOfVector = 0;

	for (int i = 0; i < numbersToAverage.size(); i++) {
		sumOfVector += numbersToAverage[i];
	}

	return sumOfVector / numbersToAverage.size();

} 

/*------------------------------------------------------------*/

float averageNumbers(std::vector<float> numbersToAverage) {
	float sumOfVector = 0;

	for (int i = 0; i < numbersToAverage.size(); i++) {
		sumOfVector += numbersToAverage[i];
	}


	return sumOfVector / numbersToAverage.size();

} 

/*------------------------------------------------------------*/

int averageNumbers(std::vector<int> numbersToAverage) {
	int sumOfVector = 0;

	for (int i = 0; i < numbersToAverage.size(); i++) {
		sumOfVector += numbersToAverage[i];
	}


	return sumOfVector / numbersToAverage.size();

} 

/*------------------------------------------------------------*/

bool isInRange(int16_t number, int16_t lower, int16_t higher) {
	if (number >= lower && number <= higher) {
		return true;
	}

	else {
		return false;
	}

}

/*------------------------------------------------------------*/

int16_t conv8b12000(float eightBitInt) {
	return eightBitInt / 127.f * 12000.f;

}

/*------------------------------------------------------------*/

int16_t conv12000to8b(float num12000) {
	return num12000 / 12000.f * 127.f;

}

/*------------------------------------------------------------*/

int8_t conv100to127(float tensNumber) {
	return tensNumber / 100 * 127;

}

/*------------------------------------------------------------*/

int8_t conv127to100(float tensNumber) {
	return tensNumber / 127 * 100;

}

/*------------------------------------------------------------*/

float convertInchesToDegrees(float inches, float wheelDiameter) {
		
	return (inches * 180 / 3.14159265) / wheelDiameter;

}

/*------------------------------------------------------------*/

uint8_t signum(double x) {
	if (x > 0) {
		return -1;
	}
    else if (x < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

/*------------------------------------------------------------*/

int getRPM(pros::Motor motor, Gearing gearing) {
    return motor.get_actual_velocity() * gearing;
}


/*------------------------------------------------------------*/

int getRPM(pros::Motor* motor, Gearing gearing) {
	return motor->get_actual_velocity() * gearing;
}

	
/*------------------------------------------------------------*/

int getRPM(pros::MotorGroup* motor, Gearing gearing) {
	return motor->get_actual_velocities()[0] * gearing;
}

/*------------------------------------------------------------*/

float pointDistanceForm(std::pair<float, float> point1, std::pair<float, float> point2) {
	return sqrt(pow(point2.first - point1.first, 2) + pow(point2.second - point1.second, 2));
}

/*------------------------------------------------------------*/