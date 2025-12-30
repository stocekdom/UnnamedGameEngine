//
// Created by dominik on 08.12.25.
//
#include "GameItemRegistry.h"
#include "GameItems.h"

GameItemRegistry::GameItemRegistry()
{
   definitions.emplace( Resources::ID_ARRAY[ Resources::ITEM_ROCKS ], ItemDefinition{
                           std::string{ Resources::ID_ARRAY[ Resources::ITEM_ROCKS ] }, "Rocks", "Rocks",
                           std::string{ Resources::TEXTURE_ARRAY[ Resources::ITEM_ROCKS ] }, ItemCategory::RESOURCE, 9999
                        } );
   definitions.emplace( Resources::ID_ARRAY[ Resources::ITEM_BERRIES ],
                        ItemDefinition{
                           std::string{ Resources::ID_ARRAY[ Resources::ITEM_BERRIES ] }, "Berries", "Berries",
                           std::string{ Resources::TEXTURE_ARRAY[ Resources::ITEM_BERRIES ] }, ItemCategory::RESOURCE, 9999
                        } );
   definitions.emplace( Resources::ID_ARRAY[ Resources::ITEM_STONE ],
                        ItemDefinition{
                           std::string{ Resources::ID_ARRAY[ Resources::ITEM_STONE ] }, "Stone", "Stone",
                           std::string{ Resources::TEXTURE_ARRAY[ Resources::ITEM_STONE ] }, ItemCategory::RESOURCE, 9999
                        } );
   definitions.emplace( Resources::ID_ARRAY[ Resources::ITEM_WOOD ],
                        ItemDefinition{
                           std::string{ Resources::ID_ARRAY[ Resources::ITEM_WOOD ] }, "Wood", "Wood",
                           std::string{ Resources::TEXTURE_ARRAY[ Resources::ITEM_WOOD ] }, ItemCategory::RESOURCE, 9999
                        } );
}
