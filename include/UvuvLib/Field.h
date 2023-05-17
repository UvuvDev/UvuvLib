#pragma once

#include "main.h"
#include "vector"

static constexpr uint8_t allianceRed = 1;
static constexpr uint8_t allianceBlue = 2;

class Field {
private:

    std::vector<std::pair<float, float>> gamePieceLocations;

    uint8_t allianceColor = allianceRed;

    std::pair<float, float> currentLocation;
    
public:

    Field(uint8_t alliance);

    void piecePickedUp();

    void piecePutDown();

    bool getShouldPieceBeHere();

};