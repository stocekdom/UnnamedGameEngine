//
// Created by dominik on 03.12.25.
//
#include "BuildingFactory.h"
#include "Concrete/PeasantHouse.h"
#include "Concrete/StoneMiner.h"

std::shared_ptr<Building> BuildingFactory::createBuilding( BuildingType type, const sf::Vector2f& position )
{
   switch( type )
   {
      // TODO add option to specify spawn category
      case BuildingType::PEASANT_HOUSE:
         return std::make_shared<PeasantHouse>( SpawnCategory::OVERLAY, position, 0, sf::Vector2f{ 0.8f, 0.8f } );
      case BuildingType::STONE_MINER:
         return std::make_shared<StoneMiner>( SpawnCategory::OVERLAY, position, 0, sf::Vector2f{ 0.8f, 0.8f } );
      default:
         break;
   }

   return nullptr;
}
