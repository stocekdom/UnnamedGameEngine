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
   enum Resource
   {
      ITEM_WOOD,
      ITEM_BERRIES,
      ITEM_ROCKS,
      ITEM_STONE,
      ITEM_COUNT,
      ITEM_NONE
   };

   // Separate enum for resource sources. Allows us to have different sources for the same item.
   // What item belongs to what source is handled inside the Resource factory
   enum ResourceSource
   {
      TREE,
      BERRY_BUSH,
      STONES,
      SOURCE_COUNT
   };

   // Centralized place storing string id's of resources. Use with Resource enum
   inline constexpr std::array<std::string_view, ITEM_COUNT> ID_ARRAY = { "res_wood", "res_berries", "res_rocks", "res_stone" };
   inline constexpr std::array<std::string_view, ITEM_COUNT> TEXTURE_ARRAY = {
      "Assets/Icons/woodIco.png", "Assets/Icons/berriesIco.png", "Assets/Icons/rocksIco.png", "Assets/Icons/stoneIco.png"
   };
   // Array of assets for resource sources. Use with ResourceSource enum
   inline constexpr std::array<std::string_view, SOURCE_COUNT> SOURCE_TEXTURE_ARRAY = {
      "Assets/Resources/trees.png", "Assets/Resources/berry1.png", "Assets/Resources/rocks.png" };
}
#endif //GAME1_RESOURCES_H
