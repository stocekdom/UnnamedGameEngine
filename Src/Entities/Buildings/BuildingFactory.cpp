//
// Created by dominik on 03.12.25.
//
#include "BuildingFactory.h"
#include "PeasantHouse.h"

std::shared_ptr<Building> BuildingFactory::createBuilding( BuildingType type, const sf::Vector2f& position )
{
   switch( type )
   {
      // TODO add option to specify spawn category
      case BuildingType::PEASANT_HOUSE:
         return std::make_shared<PeasantHouse>( SpawnCategory::OVERLAY, position, 0, sf::Vector2f{ 0.8f, 0.8f } );
      default:
         break;
   }

   return nullptr;
}

