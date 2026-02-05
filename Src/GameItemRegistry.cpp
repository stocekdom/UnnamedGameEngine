//
// Created by dominik on 08.12.25.
//
#include "GameItemRegistry.h"
#include "GameItems.h"

GameItemRegistry::GameItemRegistry()
{
   definitions.emplace( Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_ROCKS ), ItemDefinition{
                           Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_ROCKS ), "Rocks", "Rocks",
                           Resources::ResourceManager::getResourceIcon( Resources::Resource::ITEM_ROCKS ), ItemCategory::RESOURCE,
                           9999
                        } );
   definitions.emplace( Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_BERRIES ),
                        ItemDefinition{
                           Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_BERRIES ), "Berries", "Berries",
                           Resources::ResourceManager::getResourceIcon( Resources::Resource::ITEM_BERRIES ),
                           ItemCategory::RESOURCE, 9999
                        } );
   definitions.emplace( Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_STONE ),
                        ItemDefinition{
                           Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_STONE ), "Stone", "Stone",
                           Resources::ResourceManager::getResourceIcon( Resources::Resource::ITEM_STONE ), ItemCategory::RESOURCE,
                           9999
                        } );
   definitions.emplace( Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_WOOD ),
                        ItemDefinition{
                           Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_WOOD ), "Wood", "Wood",
                           Resources::ResourceManager::getResourceIcon( Resources::Resource::ITEM_WOOD ), ItemCategory::RESOURCE,
                           9999
                        } );
}
