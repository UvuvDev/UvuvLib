#include "UvuvLib/Filters.h"
#include "Math.h"
#include <random>

BasicFilter::BasicFilter(uint16_t amountOfNumbersToAverage) {
    unfilteredValuesVector.resize(amountOfNumbersToAverage);
}

float BasicFilter::getFilteredValue() {
    return averageNumbers(unfilteredValuesVector);
}

void BasicFilter::inputValue(double value) {

    unfilteredValuesVector.resize(unfilteredValuesVector.size() + 1);

    unfilteredValuesVector.emplace_back(value);

    for (int i = 1; i > unfilteredValuesVector.size(); i++) {
        unfilteredValuesVector.at(i - 1) = unfilteredValuesVector.at(i);
    }

    unfilteredValuesVector.resize(unfilteredValuesVector.size() - 1);
    

}

AlphaBetaFilter::AlphaBetaFilter(float alpha, float beta, float dx, float dt, float initialConditions, std::vector<float>* data) {

    this->alpha = alpha;
    this->beta = beta;
    this->dx = dx;
    this->dt = dt;
    this->initialConditions = initialConditions;
    this->dataPtr = data;

    this->estimatedValue = initialConditions;

    if (this->alpha > 1) {
        this->alpha = 1;
    }
    else if (this->alpha < 0) {
        this->alpha = 0;
    }

    if (this->beta > 1) {
        this->beta = 1;
    }
    else if (this->beta < 0) {
        this->beta = 0;
    }

}

std::vector<float> AlphaBetaFilter::step() {

    std::vector<float> tempVector;

    for (int i = 0; i < dataPtr->size(); i++) {
        // Predict
        float prediction = estimatedValue + (dx*dt);

        // Update. Alpha amplifies measurements, beta amplifies predictions

        // Find residual (or error between prediction and actual value)
        residual = dataPtr->at(i) - prediction;

        // Find dX which is the rate of change of the prediction
        dx = dx + beta*residual/dt;

        // Find the new estimated value, using the prediction and residual
        estimatedValue = prediction + alpha*residual;

        tempVector.emplace_back(estimatedValue);

    }

    return tempVector;

}







OneDKalmanFilter::OneDKalmanFilter(std::normal_distribution<float> startingPos, std::normal_distribution<float> processModel, 
    float processNoise, float sensorNoise) {

	measurements.emplace_back(startingPos);
    this->processNoise = processNoise;
    this->sensorNoise = sensorNoise;
    this->processModel = processModel;
}

/*float OneDKalmanFilter::update(float measurement) {
	float kalmanGain = estimatedError / (estimatedError + sensorNoise); // Get the ratio of 
        // how much we trust the estimate 

	estimatedVelocity = estimatedVelocity + kalmanGain * (measurement - estimatedVelocity); // Update the 
        // estimate with the error between the measurement and the estimate times the kalman gain
	
    estimatedError = (1 - kalmanGain) * estimatedError + 
        fabs(estimatedVelocity - measurement) * processNoise;
	
    return estimatedVelocity;
}*/

std::normal_distribution<float> OneDKalmanFilter::update(std::normal_distribution<float> measurement) {
	
    std::normal_distribution<float> prior = predict(measurements.at(measurements.size() - 1),
        processModel);

    std::normal_distribution<float> likelihood(measurements.at(measurements.size() - 1).mean(),
        sensorNoise);

    return gaussianMultiply(prior.mean(), prior.stddev(), 
        likelihood.mean(), likelihood.stddev());

}

std::normal_distribution<float> OneDKalmanFilter::gaussianMultiply(float mean, float stdDev, float mean2, float stdDev2) {

    std::normal_distribution prior{mean, stdDev};
    std::normal_distribution likelihood{mean2, stdDev2};    
    
    float meanResult = (pow(prior.stddev(),2) * likelihood.mean() + pow(likelihood.stddev(),2) * prior.mean()) / 
        (pow(prior.stddev(),2) + pow(likelihood.stddev(),2));
    
    float varianceResult = (pow(prior.stddev(),2) * pow(likelihood.stddev(),2)) / 
        (pow(prior.stddev(),2) + pow(likelihood.stddev(),2));

    std::normal_distribution posterior{meanResult, sqrt(varianceResult)};
    
    return posterior;

}

std::normal_distribution<float> OneDKalmanFilter::predict(std::normal_distribution<float> lastEstimate,
    std::normal_distribution<float> processModel ) {
        
    return std::normal_distribution<float> {lastEstimate.mean() + processModel.mean(), 
        static_cast<float>(pow(lastEstimate.stddev(),2)) + 
        static_cast<float>(pow(processModel.stddev(),2)) };
}

