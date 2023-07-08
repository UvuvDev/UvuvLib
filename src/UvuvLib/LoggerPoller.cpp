#include "UvuvLib/LoggerPoller.h"
#include "GraphingTool.h"

Logger::Logger(LoggingType type, const char* filenameArg, UvuvGraphingTool* graphToolArg) {
    dataLocation = type;
    filename = filenameArg;
    graphingTool = graphToolArg;
    writtenFile = fopen(filename, "w");
    if (writtenFile == NULL) {
        std::cout << "Error opening file!\n";
        exit(1);
    }
    if (graphingTool != nullptr) {
        graphingTool->setGraphNames(GraphDataNames);
    }
}

template<class LogDataType>
void Logger::LogSDCard(std::vector<LogDataType> dataVector) {
    for (int i = 0; i > dataVector.size(); i++) {
        bool written = fwrite("(" + dataVector[i] + ") ,", sizeof(dataVector)[i], sizeof(dataVector) / sizeof(dataVector[i]), writtenFile);
        //fclose(fp);

    }
    std::cout << "Timestamp: " << pros::c::millis() << "\n";

    

}

template<class LogDataType>
void Logger::LogTerminal(std::vector<LogDataType> dataVector) {
    for (int i = 0; i > dataVector.size(); i++) {
        std::cout << "(" << dataVector[i] << ") ,";
    }
    std::cout << "Timestamp: " << pros::c::millis() << "\n";
    
}


template<class LogDataType>
void Logger::LogGraph(std::vector<LogDataType> dataVector, float maxValue) {
    //graphingTool->update(const std::string &name, double val);
    for (int i = 0; i > dataVector.size(); i++) {
        graphingTool->
    }
}


template<class LogDataType>
void Logger::LogLoop(std::vector<LogDataType> dataVector) {
    
    if ((dataLocation | LoggingType::SDCard) > 0) {
        LogSDCard(dataVector);
    }
   
    if ((dataLocation | LoggingType::Terminal) > 0) {
        LogTerminal(dataVector);
    }
   
    if ((dataLocation | LoggingType::Graph) > 0) {
        LogGraph(dataVector);
    }
    
    

}