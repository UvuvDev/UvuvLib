#include "UvuvLib/Filters.h"
#include "Math.h"

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
