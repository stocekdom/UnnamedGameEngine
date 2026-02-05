//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_BUILDINGEVENTS_H
#define GAME1_BUILDINGEVENTS_H

#include "Buildings.h"

struct BuildingPlacingStarted
{
   Buildings::BuildingType type = Buildings::BuildingType::NO_BUILDING;
   sf::Vector2f position;
};

#endif //GAME1_BUILDINGEVENTS_H
