//
// Created by dominik on 03.12.25.
//
#include "BuildingFactory.h"

#include "BuildingSprites.h"
#include "Concrete/PeasantHouse.h"
#include "Concrete/StoneMiner.h"

std::shared_ptr<Building> BuildingFactory::createBuilding( GameScene* scene, BuildingType type, const sf::Vector2f& position )
{
   switch( type )
   {
      case BuildingType::PEASANT_HOUSE:
      {
         auto b = scene->createFunctionalEntity<PeasantHouse>( ActorParams{ position } );
         addComponent( scene, b->getEntityId(), type );
         return b;
      }
      case BuildingType::STONE_MINER:
      {
         auto b = scene->createFunctionalEntity<StoneMiner>( ActorParams{ position } );
         addComponent( scene, b->getEntityId(), type );
         return b;
      }
      default:
         break;
   }

   return nullptr;
}

void BuildingFactory::addComponent( GameScene* scene, Entity entity, BuildingType type )
{
   scene->addComponent<OverlaySpriteComponent>( entity, entity,
                                                std::string{ BuildingSprites::buildingSprites[ type ] } );
}
