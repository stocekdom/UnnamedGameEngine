//
// Created by dominik on 08.12.25.
//
#include "GameItemRegistry.h"
#include "Resources.h"

GameItemRegistry::GameItemRegistry()
{
   definitions.emplace( Resources::ID_ARRAY[ Resources::ITEM_ROCKS ], ItemDefinition{
                           Resources::ID_ARRAY[ Resources::ITEM_ROCKS ], "Rocks", "Rocks",
                           Resources::TEXTURE_ARRAY[ Resources::ITEM_ROCKS ], ItemCategory::RESOURCE, 9999
                        } );
   definitions.emplace( Resources::ID_ARRAY[ Resources::ITEM_BERRIES ],
                        ItemDefinition{
                           Resources::ID_ARRAY[ Resources::ITEM_BERRIES ], "Berries", "Berries",
                           Resources::TEXTURE_ARRAY[ Resources::ITEM_BERRIES ], ItemCategory::RESOURCE, 9999
                        } );
   definitions.emplace( Resources::ID_ARRAY[ Resources::ITEM_STONE ],
                        ItemDefinition{
                           Resources::ID_ARRAY[ Resources::ITEM_STONE ], "Stone", "Stone",
                           Resources::TEXTURE_ARRAY[ Resources::ITEM_STONE ], ItemCategory::RESOURCE, 9999
                        } );
   definitions.emplace( Resources::ID_ARRAY[ Resources::ITEM_WOOD ],
                        ItemDefinition{
                           Resources::ID_ARRAY[ Resources::ITEM_WOOD ], "Wood", "Wood",
                           Resources::TEXTURE_ARRAY[ Resources::ITEM_WOOD ], ItemCategory::RESOURCE, 9999
                        } );
}
