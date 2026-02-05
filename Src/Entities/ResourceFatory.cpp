//
// Created by dominik on 16.12.25.
//

#include "ResourceFactory.h"

std::shared_ptr<ResourceActor> ResourceFactory::createResource( GameScene* scene, Resources::ResourceSource resource,
                                                                const sf::Vector2f& position )
{
   switch( resource )
   {
      // ResourceActor ctor: Resources::Resource, Resources::ResourceSource, float harvestTime, unsigned int harvestAmount, unsigned int amount
      case Resources::ResourceSource::BERRY_BUSH:
         // TODO Add random amount in range

         return scene->createFunctionalEntity<ResourceActor>( Resources::Resource::ITEM_BERRIES,
                                                              Resources::ResourceSource::BERRY_BUSH, 10, 1, 9999,
                                                              ActorParams( position ) );

      case Resources::ResourceSource::STONES:
         return scene->createFunctionalEntity<ResourceActor>( Resources::Resource::ITEM_ROCKS, Resources::ResourceSource::STONES,
                                                              10, 5, 9999, ActorParams( position ) );

      case Resources::ResourceSource::TREE:
         return scene->createFunctionalEntity<ResourceActor>( Resources::Resource::ITEM_WOOD, Resources::ResourceSource::TREE, 15,
                                                              10, 9999, ActorParams( position ) );

      default:
         return nullptr;
   }
}
