
#include "main.h"
#include <random>

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
 * @brief It's a 1D Kalman filter. Best used for 1D systems, not 2D or 3D.
 * 
 */
class OneDKalmanFilter {
private:
    
    std::normal_distribution<float> processModel;

    std::vector<std::normal_distribution<float>> measurements;

    float processNoise = 0;
    float sensorNoise = 0;

    float estimatedError = 0;
    float estimatedVelocity = 0;

    float kGain = 0;

    float lastEstimatedError = 0;
    float lastEstimatedVelocity = 0;

    float lastEstimatedValue = 0;

    float lastSensorValue = 0;

    /**
     * @brief Just adds two Gaussians together to make a prediction.
     * 
     * @param lastEstimate The previous estimate on the system. 
     * @param processModel The model chosen for the system.
     * @return std::normal_distribution<float> 
     */
    std::normal_distribution<float> predict(std::normal_distribution<float> lastEstimate,
    std::normal_distribution<float> processModel );
        
    /**
     * @brief Multiply two gaussians together.
     * 
     * @param mean    Mean for Gaussian 1
     * @param stdDev  Standard Deviation for Gaussian 1
     * @param mean2   Mean for Gaussian 2
     * @param stdDev2 Standard Deviation for Gaussian 2
     * @return std::normal_distribution<> 
     */
    std::normal_distribution<float> gaussianMultiply(float mean, float stdDev, float mean2, float stdDev2);



protected:

public:

    OneDKalmanFilter(std::normal_distribution<float> startingPos,  std::normal_distribution<float> processModel,
        float processNoise, float sensorNoise);

    std::normal_distribution<float> update(std::normal_distribution<float> measurement);

};

/**
 * @brief 
 * 
 */
class ExtendedKalmanFilter : public OneDKalmanFilter{
private:

protected:

public:

};
