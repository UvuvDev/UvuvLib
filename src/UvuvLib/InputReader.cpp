
#include "UvuvLib/InputReader.h"


int16_t InputReader::readInputsMap[inputSourceNum][inputMapLength];
int16_t InputReader::readInputsBuffer[inputSourceNum * inputMapLength];


InputReader::InputReader(UvuvBasicController* controllerArg) {
    Uvuv_Controller = controllerArg;
}

InputReader::InputReader(pros::Controller* controllerArg) {
    PROS_Controller = controllerArg;
}

/*------------------------------------------------------------*/

void InputReader::waitTime(int globalTick, uint16_t intervalToWait) {
    while (pros::c::millis() < (uint32_t)intervalToWait * (uint32_t)globalTick) {
    }
    
}

/*------------------------------------------------------------*/

void InputReader::replayInputs(uint16_t globalTick) {
    while (1) {
        std::cout << readInputsMap[0][globalTick];
        std::cout << readInputsMap[1][globalTick];
        globalTick++;
        waitTime(globalTick, 20);
        
        

    }
}

/*------------------------------------------------------------*/

void InputReader::writeInputsToSD(FILE* fp) { 
    std::cout << "Writing Inputs to SD...\n\n";
    for (int i = 0; i < inputMapLength; i++) {
        for (uint8_t f = 0; f < inputSourceNum; f++) {
            readInputsBuffer[(i * inputSourceNum) + f] = readInputsMap[f][i];
        }
    }

    bool x = fwrite(readInputsBuffer, sizeof(readInputsBuffer)[0], sizeof(readInputsBuffer) / sizeof(readInputsBuffer[0]), fp);
    fclose(fp);
    if (x == true) {
        std::cout << "Inputs are Written!\n\n";
    }
    else {
        std::cout << "Something went wrong...\n\n";
    }
    
    
    
}

/*------------------------------------------------------------*/

void InputReader::loadInputsFromSD(FILE* fp) { // 8 Inputs 3000 times
    
    FILE* usd_file_read = fopen("/usd/example.txt", "r");
    fread(readInputsBuffer, sizeof(readInputsBuffer)[0], sizeof(readInputsBuffer) / sizeof(readInputsBuffer[0]), usd_file_read);
    fclose(usd_file_read);		
    std::cout << readInputsBuffer;
    
    for (int i = 0; i < inputMapLength; i++) {
        for (uint8_t f = 0; f < inputSourceNum; f++) {
            readInputsBuffer[(i * inputMapLength) + f] = readInputsMap[i][f];
        }
    }
}

/*------------------------------------------------------------*/

void InputReader::inputsIntoMap(int globalTick) {
    
    readInputsMap[0][globalTick] = 0;
    readInputsMap[1][globalTick] = 0;
    readInputsMap[2][globalTick] = 0;
    readInputsMap[3][globalTick] = 0;
    readInputsMap[4][globalTick] = 0;
    readInputsMap[5][globalTick] = 0;
    readInputsMap[6][globalTick] = 0;
    readInputsMap[7][globalTick] = 0;
    
}

/*------------------------------------------------------------*/

void InputReader::quickSaver() {
    for (int f = 0; f <= inputMapLength; f++) {
        for (int i = 0; i <= inputSourceNum; i++) {
            readInputsMap[f][i] = 1;
        }
    }
    
}

/*------------------------------------------------------------*/


