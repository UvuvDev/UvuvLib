#pragma once

#include "main.h"
#include "Math.h"
#include "UvuvController.h"

class InputReader {
private:

    UvuvBasicController* Uvuv_Controller; // Pointer to the Uvuv controller
    pros::Controller* PROS_Controller; // Pointer to the PROS controller

    static constexpr uint16_t inputMapLength = 100; // Number of ticks to save inputs for. After the tick limit is reached, the 
        // inputs will no longer be saved.
    static constexpr uint8_t inputSourceNum = 8; // The number of input sources per section of the input map.

public:

    static int16_t readInputsMap[inputSourceNum][inputMapLength]; // Stores all inputs

    InputReader(UvuvBasicController* controllerArg);

    InputReader(pros::Controller* controllerArg);

    ~InputReader();

protected:

    static int16_t readInputsBuffer[inputSourceNum * inputMapLength]; // The buffer between the read inputs and a save file.
   
    /**
     * @brief Waits for a certain amount of time. 100% accurate to the microsecond, to prevent any slight errors.
     * 
     * @param globalTick 
     * @param intervalToWait 
     */
    void waitTime(int globalTick, uint16_t intervalToWait);  
    
    /**
     * @brief Replays the inputs.
     * 
     * @param globalTick The global tick, used to determine where to begin playback.
     */
    void replayInputs(uint16_t globalTick);
   
    /**
     * @brief Writes the inputs to the SD Card.
     * 
     * @param fp A pointer to the file to write to.
     */
    void writeInputsToSD(FILE* fp);
   
    /**
     * @brief Loads the inputs from the SD Card.
     * 
     * @param fp A pointer to the file to read from.
     */
    void loadInputsFromSD(FILE* fp);
   
    /**
     * @brief Saves the inputs from the controller at any given tick. 
     * 
     * @param globalTick 
     * @param Controller1 
     */
    void inputsIntoMap(int globalTick); // Saves inputs from controller into the map.
   
    /**
     * @brief Saves a random junk input map, only for debugging.
     * 
     */
    void quickSaver(); 
   

};
