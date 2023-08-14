
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




class AlphaBetaFilter {
private:

    float alpha;
    float beta;

    float residual;
    float dx;
    float dt;
    float initialConditions;
    float estimatedValue;

    std::vector<float>* dataPtr;
    

public:

    /**
     * @brief Construct a new Alpha Beta Filter. 
     * 
     * @param alpha Alpha (or G) is a measure of how much you trust your measurements. Between 0.0-1.0. 
     *  Higher = more trust in the measurements, lower = less.
     * @param beta Beta (or H) is a measure of how much you trust your own predictions. Between 0.0-1.0. 
     *  Higher = more trust in the predictions, lower = less.
     * @param dx First change in rate
     * @param dt Change in time.
     * @param initialConditions The initial value of the system. If it was coordinates, you'd use (0,0) 
     * probably.
     * @param data A pointer to all the data. Up to you to update the data with your measurements, which the 
     * A,B filter points to automatically in step().
     *
     * https://nbviewer.org/github/rlabbe/Kalman-and-Bayesian-Filters-in-Python/blob/master/01-g-h-filter.ipynb
     * 
     *                              ^ 
     * Good resource for the Alpha Beta filter. In here it's called a G-H filter.
     */
    AlphaBetaFilter(float alpha, float beta, float dx, float dt, float initialConditions, std::vector<float>* data);

    std::vector<float> step();



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
