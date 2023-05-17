
#include "main.h"

/**
 * @brief Basic Filter. Simply averages a set of values you input.
 * 
 */
class BasicFilter {
private:

protected:

    std::vector<float> unfilteredValuesVector;

public:

    BasicFilter(uint16_t amountOfNumbersToAverage);

    float getFilteredValue();

    void inputValue(double value);

};


/**
 * @brief Similar to the Basic Filter but it also comes with a capper, that way any weird crazy values can
 * be rounded up to or down to whatever you say.
 * 
 */
class RandomFilter : public BasicFilter {
private:

protected:

public:

    RandomFilter(double maxValue, double minValue);

    void inputValue(double value);

};


/**
 * @brief Filter that filters vectors. You input a pointer to the vector, and the filter
 * filters it on your behalf to get rid of anything. 
 * 
 */
class VectorFilter {
private:

protected:

public:

    VectorFilter();

    void filterVector(std::vector<float>* unfilteredVector);
    
};


/**
 * @brief Kalman Filter lol
 * 
 */
class KalmanFilter {
private:

protected:

public:

};