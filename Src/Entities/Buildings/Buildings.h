//
// Created by dominik on 28.12.25.
//

#ifndef GAME1_BUILDINGS_H
#define GAME1_BUILDINGS_H

#include "../../../Base/Core/Util.h"
#include <array>
#include <span>
#include <string>

#include "../../GameItems.h"

namespace Buildings
{
   enum class BuildingType
   {
      PEASANT_HOUSE,
      STONE_MINER,
      COUNT,
      NO_BUILDING,
   };

   struct CostRequirement
   {
      Resources::Resource resourceId;
      unsigned int amount;
   };

   class BuildingCostManager
   {
      public:
         static std::span<const CostRequirement> getCost( BuildingType type )
         {
            if( type > BuildingType::COUNT ) [[unlikely]]
                  return {};
            return costTable[ Util::enumToIndex( type ) ];
         }

      private:
         static constexpr std::array<CostRequirement, 1> peasantHouseCost = {
            CostRequirement{ Resources::Resource::ITEM_WOOD, 3 },
         };

         static constexpr std::array<CostRequirement, 1> stoneMinerCost = {
            CostRequirement{ Resources::Resource::ITEM_WOOD, 5 },
         };

         static constexpr std::array<std::span<const CostRequirement>, Util::enumToIndex( BuildingType::COUNT )> costTable = {
            std::span{ peasantHouseCost },
            std::span{ stoneMinerCost },
         };
   };

   class BuildingSpritesManager
   {
      public:
         static std::string getBuildingTexture( BuildingType type )
         {
            if( type > BuildingType::COUNT ) [[unlikely]]
                  return "";
            return std::string{ buildingSprites[ Util::enumToIndex( type ) ] };
         }

      private:
         static constexpr std::array<std::string_view, Util::enumToIndex( BuildingType::COUNT )> buildingSprites = {
            "Assets/Buildings/house1.png", "Assets/Buildings/stoneMiner.png"
         };
   };
}

#endif //GAME1_BUILDINGS_H
