#pragma once
#include "main.h"
#include "GraphingTool.h"

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
    UvuvGraphingTool* graphingTool;
    std::vector<std::string> GraphDataNames;

    std::string nameOfLog;
    
public:

    bool setTimestamp = true;

    /**
     * @brief Construct a new Logger object
     * 
     * @param type 
     * @param filenameArg Must have /usd/ at the beginning. Otherwise it won't work.
     * @param graphToolArg 
     */
    Logger(std::string nameOfLogArg, LoggingType type, const char* filenameArg = "/usd/LOG.txt", UvuvGraphingTool* graphToolArg = nullptr);

    ~Logger();

    template<class LogDataType>
    void LogSDCard(std::vector<LogDataType>* dataVector);

    template<class LogDataType>
    void LogTerminal(std::vector<LogDataType>* dataVector);

    template<class LogDataType>
    void LogGraph(std::vector<LogDataType>* dataVector);

    /**
     * @brief Logs the data to the location specified in the constructor.
     * 
     * @tparam LogDataType 
     * @param dataVector Pointer to the vector of data to be logged.
     * @param delayTimeMillis How long to wait between logging.
     */
    template<class LogDataType>
    void LogLoop(std::vector<LogDataType>* dataVector, int delayTimeMillis = 20);



};

class Poller {
private:

    FILE* filePointer; // Pointer to the file the Poller will be reading from. 

    int bufferLength = 0; // Length of the buffer to read from the file. 

    std::vector<char> fileContent; // Content of the file. Will have to be parsed through after obtaining. 

protected:

public: 

    /**
     * @brief Construct a new Poller object.
     * 
     * @param filePointerArg Pointer to the file being read.
     * @param bufferLengthArg The length of the data being read. VERY IMPORTANT!!
     */
    Poller(FILE* filePointerArg, int bufferLengthArg);

    ~Poller();

    /**
     * @brief Get the Data from the SD Card.
     * 
     * @return std::vector<char> 
     */
    std::vector<char> getData();


};