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