#include "UvuvLib/GraphingTool.h"

UvuvGraphingTool::UvuvGraphingTool(std::string title, std::pair<int, int> minAndMaxRangeArg, int updateRateInMsArg, 
    bool zoomInArg, bool zoomOutArg) {


}

void UvuvGraphingTool::beginGraphing() {

}

void UvuvGraphingTool::stopGraphing() {

}

void UvuvGraphingTool::addInputs(std::vector<std::pair<double*, std::string>> ptrsToInputsArg) {

}

void UvuvGraphingTool::activateZoomIn() {

}

void UvuvGraphingTool::activateZoomOut() {

}

std::map<std::string, std::vector<double>>* UvuvGraphingTool::getGraphDataPoints() {

    return nullptr;
}

void insertNewCompletedGraph(std::string newGraphTitle, std::vector<double>* newGraphValues) {

}

graphy::AsyncGrapher* UvuvGraphingTool::getGraphyGraph() {
    return graphyBaseGrapher;
}
