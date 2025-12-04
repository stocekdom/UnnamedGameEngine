//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_BUILDINGEVENTS_H
#define GAME1_BUILDINGEVENTS_H

#include "BuildingType.h"

struct BuildingPlacingStarted
{
   BuildingType type = BuildingType::NONE;
   sf::Vector2f position;
};

#endif //GAME1_BUILDINGEVENTS_H
