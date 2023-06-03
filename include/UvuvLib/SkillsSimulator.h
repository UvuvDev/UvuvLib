
#include "UvuvController.h"
#include "AutonSelector.h"


class SkillsSimulation {
private:

    UvuvBasicController* controller;

    AutonSelector* autonSelector;

    void countdown();

public:

    SkillsSimulation(UvuvBasicController* controllerArg, AutonSelector* autonSelectorArg = nullptr);

    ~SkillsSimulation();
    
    void runSimulation();

    void restart();


};