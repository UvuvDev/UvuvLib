
#include <fstream>

#include "UvuvLib/LoggerPoller.h"


Logger::Logger(std::string nameOfLogArg, LoggingType type, const char* filenameArg, UvuvGraphingTool* graphToolArg) {
    dataLocation = type;
    filename = filenameArg;
    graphingTool = graphToolArg;
    writtenFile = fopen(filename, "w");
    nameOfLog = nameOfLogArg;
    if (writtenFile == NULL) {
        std::cout << "Error opening file!\n";
        exit(1);
    }
    if (graphingTool == nullptr) {
        graphingTool = new UvuvGraphingTool(nameOfLog, {0, 100}, 20, 
            true, false);
    }
}

Logger::~Logger() {
    fclose(writtenFile);
    delete graphingTool;
}

template<class LogDataType>
void Logger::LogSDCard(std::vector<LogDataType>* dataVector) {

    for (int i = 0; i > dataVector->size(); i++) {
        bool written = fwrite("(" + dataVector[i] + ") ,", sizeof(dataVector)[i], sizeof(&dataVector) / sizeof(dataVector[i]), writtenFile);
        //fclose(fp);

    }
    

    

}

template<class LogDataType>
void Logger::LogTerminal(std::vector<LogDataType>* dataVector) {

    for (int i = 0; i > dataVector->size(); i++) {
        std::cout << "(" << dataVector[i] << ") ,";
    }
    
}


template<class LogDataType>
void Logger::LogGraph(std::vector<LogDataType>* dataVector) {

    static bool firstRuntime = true;

    if (graphingTool != nullptr && firstRuntime) {
        graphingTool->addInputs(dataVector);
        firstRuntime = false;
    }

    std::cout << "Graphed!   ";
    std::cout << "Timestamp: " << (float)pros::c::millis() / 1000 << "\n";

}


template<class LogDataType>
void Logger::LogLoop(std::vector<LogDataType>* dataVector, int delayTimeMillis) {

    static bool firstRuntimeSDCard = true;

    if ((dataLocation | LoggingType::SDCard) > 0 && firstRuntimeSDCard) {
        pros::Task task{[=] {
            pros::delay(delayTimeMillis);
            std::cout << "Logged to SD Card!   ";
            std::cout << "Timestamp: " << (float)pros::c::millis() / 1000 << "\n";
            LogSDCard(dataVector);
        }};
        firstRuntimeSDCard = false;
        
    }

    static bool firstRuntimeTerminal = true;
   
    if ((dataLocation | LoggingType::Terminal) > 0 && firstRuntimeTerminal) {
        pros::Task task{[=] {
            std::cout << "Log for: " << nameOfLog << " ---- ";
            pros::delay(delayTimeMillis);
            std::cout << "Logged to Terminal!   ";
            std::cout << "Timestamp: " << (float)pros::c::millis() / 1000 << "\n";
            LogTerminal(dataVector);
        }};
        firstRuntimeTerminal = false;
        
    }
   
    static bool firstRuntimeGraph = true;

    if ((dataLocation | LoggingType::Graph) > 0 && firstRuntimeGraph) {
        LogGraph(dataVector);
        graphingTool->beginGraphing();
        firstRuntimeGraph = false;
        
    }   

}








Poller::Poller(FILE* filePointerArg, int bufferLengthArg) {
    filePointer = filePointerArg;
    bufferLength = bufferLengthArg;
    fileContent.resize(bufferLengthArg);
}

Poller::~Poller() {
    fclose(filePointer);
}

std::vector<char> Poller::getData() {

    fread(&fileContent, sizeof(fileContent)[0], (fileContent.size()) / sizeof(fileContent[0]), filePointer);

    fclose(filePointer);	

    return fileContent;

}