//
// Created by dominik on 07.12.25.
//

#ifndef GAME1_RESOURCES_H
#define GAME1_RESOURCES_H

// Centralized resource IDs
#include <string>
#include <array>

#include "../Base/Core/Utility.h"

// TODO might need to break up to individual files once we have a lot of items
/**
 * Stores all resource IDs in a centralized place.
 * To get the resource ID for a specific item, use the ID_ARRAY array with the item's enum value as index.
 */
namespace Resources
{
   enum class Resource
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
   enum class ResourceSource
   {
      TREE,
      BERRY_BUSH,
      STONES,
      SOURCE_COUNT
   };

   class ResourceManager
   {
      public:
         static std::string getResourceId( unsigned int resource )
         {
            if( resource >= ID_ARRAY.size() ) [[unlikely]]
               return "";
            return std::string{ ID_ARRAY[ resource ] };
         }

         static std::string getResourceId( Resource resource )
         {
            if( resource > Resource::ITEM_COUNT ) [[unlikely]]
               return "";
            return std::string{ ID_ARRAY[ Utility::enumToIndex( resource ) ] };
         }

         static std::string getResourceIcon( Resource resource )
         {
            if( resource > Resource::ITEM_COUNT ) [[unlikely]]
               return "";
            return std::string{ TEXTURE_ARRAY[ Utility::enumToIndex( resource ) ] };
         }

         static std::string getResourceSourceTexture( ResourceSource source )
         {
            if( source > ResourceSource::SOURCE_COUNT ) [[unlikely]]
               return "";
            return std::string{ SOURCE_TEXTURE_ARRAY[ Utility::enumToIndex( source ) ] };
         }

      private:
         // TODO use std::span for variants
         // Centralized place storing string id's of resources. Use with Resource enum
         static constexpr std::array<std::string_view, Utility::enumToIndex( Resource::ITEM_COUNT )> ID_ARRAY = {
            "res_wood", "res_berries", "res_rocks", "res_stone"
         };
         static constexpr std::array<std::string_view, Utility::enumToIndex( Resource::ITEM_COUNT )> TEXTURE_ARRAY = {
            "Assets/Icons/woodIco.png", "Assets/Icons/berriesIco.png", "Assets/Icons/rocksIco.png", "Assets/Icons/stoneIco.png"
         };
         // Array of assets for resource sources. Use with ResourceSource enum
         static constexpr std::array<std::string_view, Utility::enumToIndex( ResourceSource::SOURCE_COUNT )> SOURCE_TEXTURE_ARRAY
               = {
                  "Assets/Resources/trees.png", "Assets/Resources/berry1.png", "Assets/Resources/rocks.png"
               };
   };
}
#endif //GAME1_RESOURCES_H
