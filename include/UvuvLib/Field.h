#pragma once

#include "main.h"
#include "vector"
#include "Definitions.h"

static constexpr uint8_t allianceRed = 1;
static constexpr uint8_t allianceBlue = 2;

class Field {
private:

    std::vector<std::pair<float, float>> gamePieceLocations;

    std::pair<float, float> gamePieceMaxDimensions;

    BotDimensions* botDimensions;

    Alliance allianceColor = Alliance::E_ALLIANCE_RED;
    
public:

    Field(Alliance alliance, BotDimensions* botDimensionsArg);

    void piecePickedUp(std::pair<float, float> currentLocation);

    void piecePutDown(std::pair<float, float> currentLocation);

    int getShouldPieceBeHere(std::pair<float, float> currentLocation);

};