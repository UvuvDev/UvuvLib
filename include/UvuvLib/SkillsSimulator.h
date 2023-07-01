
#include "UvuvController.h"
#include "AutonSelector.h"
#include "InputReader.h"
#include "LoggerPoller.h"
#include "ShapesAndCoords.h"

std::string testString;

class SkillsSimulation {
private:

    int amountOfSkillsSimsDone; // The amount of skills simulations that have been done. Used for saving the data to the
        // file.

    UvuvBasicController* controller; // Pointer to the controller driver is using 

    AutonSelector* autonSelector; // A pointer to the auton selector, so you can pick which auton is being run

    InputReader* inputReader; // A pointer to the input reader, to track misinputs

    Logger* logger; // Logger for the saving the simulation results

    Poller* poller; // Poller for getting past simulation results

    std::vector<Circle> circles; // Vector of circles that will be used for the performance evaluation

    std::vector<float> times; // Vector of times that the driver took to complete go through each circle

    float lastTimeEnteredCircle; // The time that the driver last entered a circle, used for calculating the time it took
        // to go through the circle. Recorded in milliseconds.

    Rectangle botDimensions; // Rectangle with the dimensions of the bot. Be as accurate as possible, as this
        // will be used for the performance evaluation. Only measure relevant things: an axle sticking out of the bot
        // or a random piece of metal that doesn't affect the bot's performance doesn't need to be included. However,
        // if you have a mechanism that extends out of the bot, that should be included.
    
    /**
     * @brief The regular "3, 2, 1" from the controller when starting a skills run
     * 
     */
    void countdown(); 

    /**
     * @brief Mark the time when the driver goes through a circle
     * 
     * @param circleIndex Which circle the driver is going through, as an index for the vector of circles
     */
    void markTime(int circleIndex); 

    /**
     * @brief Save the data to the SD card. Things like the times for each circle, percent performance.
     * 
     */
    void saveData(); // Save the data to the SD card

    
    


public:

    /**
     * @brief Construct a new Skills Simulation object
     * 
     * @param controllerArg Pointer to the controller the driver is using
     * @param autonSelectorArg Pointer to the auton selector that can be either inputted or not. If not inputted, the 
     * auton will not be run and by default driver control will run.
     * @param inputReaderArg Pointer to the input reader that can be either inputted or not. If not inputted, the
     */
    SkillsSimulation(UvuvBasicController* controllerArg, AutonSelector* autonSelectorArg = nullptr, InputReader* inputReaderArg = nullptr);

    /**
     * @brief Destroy the Skills Simulation object
     * 
     */
    ~SkillsSimulation();

    /**
     * @brief Begin Simulating
     * 
     */
    void runSimulation();

    /**
     * @brief Restart the simulation
     * 
     */
    void restart();  // Probably will be tied to a button on the controller

    /**
     * @brief Get the Percentage Performance of the driver in the simulation
     * 
     * @return Range 
     */
    Range getPercentagePerformance();


};