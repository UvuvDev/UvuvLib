#include "UvuvLib/Field.h"
#include "Definitions.h"

Field::Field(Alliance alliance, BotDimensions* botDimensionsArg) {
    allianceColor = alliance;
    botDimensions = botDimensionsArg;

}

void Field::piecePickedUp(std::pair<float, float> currentLocation) {

    int pieceIndex = getShouldPieceBeHere(currentLocation);

    if (pieceIndex != -1) {
        gamePieceLocations.erase(gamePieceLocations.begin() + pieceIndex);
    }


}

void Field::piecePutDown(std::pair<float, float> currentLocation) {
    gamePieceLocations.emplace_back(std::pair<float, float>(currentLocation.first, currentLocation.second));
}

int Field::getShouldPieceBeHere(std::pair<float, float> currentLocation) {

    /*
    rect1.x < rect2.x + rect2.w &&
    rect1.x + rect1.w > rect2.x &&
    rect1.y < rect2.y + rect2.h &&
    rect1.y + rect1.h > rect2.y */

    for (int i = 0; gamePieceLocations.size() > 0; i++ ) {
        
        if ( gamePieceLocations[i].first < currentLocation.first + botDimensions->width 
            && gamePieceLocations[i].first + gamePieceMaxDimensions.first > currentLocation.first
            && gamePieceLocations[i].second < currentLocation.second + botDimensions->length
            && gamePieceLocations[i].second + gamePieceMaxDimensions.second > currentLocation.second) {
        
                return i;
        }
        
    }

    return -1;

}