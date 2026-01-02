//
// Created by dominik on 28.12.25.
//

#ifndef GAME1_BUILDINGSPRITES_H
#define GAME1_BUILDINGSPRITES_H
#include <array>
#include <string>

#include "BuildingType.h"

namespace BuildingSprites
{
   inline constexpr std::array<std::string_view, BuildingType::COUNT> buildingSprites = {
      "Assets/Buildings/house1.png", "Assets/Buildings/stoneMiner.png"
   };
}

#endif //GAME1_BUILDINGSPRITES_H
