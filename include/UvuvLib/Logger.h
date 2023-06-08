#pragma once
#include "main.h"
#include "Graphy/Grapher.hpp"

typedef enum {

    SDCard = 1,
    Terminal = 2, 
    BrainScreen = 4,
    Graph = 8
    
} LoggingType;

class Logger {
protected:
    uint8_t dataLocation = 0;
    const char * filename = "/usd/LOG.txt";
    FILE* writtenFile;
    graphy::AsyncGrapher* graphingTool;
    std::vector<std::string> GraphDataNames;
    
public:

    bool setTimestamp = true;

    /**
     * @brief Construct a new Logger object
     * 
     * @param type 
     * @param filenameArg Must have /usd/ at the beginning. Otherwise it won't work.
     * @param graphToolArg 
     */
    Logger(LoggingType type, const char* filenameArg = "/usd/LOG.txt", graphy::AsyncGrapher* graphToolArg = nullptr);

    template<class LogDataType>
    void LogSDCard(std::vector<LogDataType> dataVector);

    template<class LogDataType>
    void LogTerminal(std::vector<LogDataType> dataVector);

    template<class LogDataType>
    void LogGraph(std::vector<LogDataType> dataVector, float maxValue);

    template<class LogDataType>
    void LogLoop(std::vector<LogDataType> dataVector);



};

class Poller {

};