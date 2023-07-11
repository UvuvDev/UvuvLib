#pragma once

#include "Graphy/Grapher.hpp"

class UvuvGraphingTool {
private:

    std::pair<int, int> minAndMaxRangeArg;

    graphy::AsyncGrapher* graphyBaseGrapher;

    bool zoomIn = false;
    bool zoomOut = false;

    std::vector<std::pair<double*, std::string>> ptrsToInputs; // Ptrs to inputs and their name

    int updateRate = 10;

public:

    UvuvGraphingTool(std::string title, std::pair<int, int> minAndMaxRangeArg, int updateRateInMsArg, bool zoomInArg = false, bool zoomOutArg = false);

    void beginGraphing(); // Start Task

    void stopGraphing();

    /**
     * @brief Adds inputs into the graph. **ONLY ACTIVATE ONCE PER ITEM, WILL CRASH OTHERWISE**
     * 
     * @param ptrsToInputsArg Takes a pointer to a double and a string for its name as parameters.
     */
    void addInputs(std::vector<std::pair<double*, std::string>> ptrsToInputsArg); // ONLY DO ONCE PER ITEM

    /**
     * @brief Turns on Zoom In, meaning that the graph zooms into the relevant areas, Min and Max dynamically
     * change. Turns off Zoom Out. 
     *
     */
    void activateZoomIn();

    /**
     * @brief Turns on Zoom In, meaning that the graph zooms out to the lowest and highest recorded value.
     * Turns off Zoom In. 
     *
     */
    void activateZoomOut();

    /**
     * @brief Get the recent (i.e. visible) data points on the graph.
     * 
     * @return std::map<std::string, std::vector<double>>* of data points.
     */
    std::map<std::string, std::vector<double>>* getGraphDataPoints();
    
    /**
     * @brief Inserts a graph that already has data points.
     * 
     * @param newGraphTitle
     * @param newGraphValues 
     */
    void insertNewCompletedGraph(std::string newGraphTitle, std::vector<double>* newGraphValues);

    /**
     * @brief Get the Grapher object
     * 
     * @return graphy::AsyncGrapher* 
     */
    graphy::AsyncGrapher* getGraphyGraph();

};