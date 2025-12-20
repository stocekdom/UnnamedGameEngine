//
// Created by dominik on 07.12.25.
//

#ifndef GAME1_RESOURCES_H
#define GAME1_RESOURCES_H

// Centralized resource IDs
#include <string>
#include <array>

/**
 * Stores all resource IDs in a centralized place.
 * To get the resource ID for a specific item, use the ID_ARRAY array with the item's enum value as index.
 */
namespace Resources
{
   enum ItemID
   {
      ITEM_WOOD,
      ITEM_BERRIES,
      ITEM_ROCKS,
      ITEM_STONE,
      ITEM_COUNT
   };

   inline const std::array<std::string, ITEM_COUNT> ID_ARRAY = { "res_wood", "res_berries", "res_rocks", "res_stone" };
   inline const std::array<std::string, ITEM_COUNT> TEXTURE_ARRAY = {
      "Assets/Icons/woodIco.png", "Assets/Icons/berriesIco.png", "Assets/Icons/rocksIco.png", "Assets/Icons/stoneIco.png"
   };
}
#endif //GAME1_RESOURCES_H
