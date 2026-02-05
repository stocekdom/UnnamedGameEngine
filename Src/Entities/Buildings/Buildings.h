//
// Created by dominik on 28.12.25.
//

#ifndef GAME1_BUILDINGS_H
#define GAME1_BUILDINGS_H

#include "../../../Base/Core/Utility.h"
#include <array>
#include <string>

namespace Buildings
{
   enum class BuildingType
   {
      PEASANT_HOUSE,
      STONE_MINER,
      COUNT,
      NO_BUILDING,
   };

   class BuildingSpritesManager
   {
      public:
         static std::string getBuildingTexture( BuildingType type )
         {
            if( type > BuildingType::COUNT ) [[unlikely]]
               return "";
            return std::string{ buildingSprites[ Utility::enumToIndex( type ) ] };
         }

      private:
         static constexpr std::array<std::string_view, Utility::enumToIndex( BuildingType::COUNT )> buildingSprites = {
            "Assets/Buildings/house1.png", "Assets/Buildings/stoneMiner.png"
         };
   };
}

#endif //GAME1_BUILDINGS_H
