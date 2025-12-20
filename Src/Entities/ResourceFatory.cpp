//
// Created by dominik on 16.12.25.
//

#include "ResourceFactory.h"

std::shared_ptr<ResourceActor> ResourceFactory::createResource( Resources::ResourceSource resource,
                                                                const sf::Vector2f& position )
{
   switch( resource )
   {
      case Resources::ResourceSource::BERRY_BUSH:
         // TODO Add random amount in range
         return std::make_shared<ResourceActor>( position, 0, sf::Vector2f{ 1.f, 1.f }, true, 9999,
                                                 Resources::Resource::ITEM_BERRIES, Resources::ResourceSource::BERRY_BUSH, 10 );

      case Resources::ResourceSource::STONES:
         return std::make_shared<ResourceActor>( position, 0, sf::Vector2f{ 1.f, 1.f }, true, 4000,
                                        Resources::Resource::ITEM_ROCKS, Resources::ResourceSource::STONES, 5, 5 );

      case Resources::ResourceSource::TREE:
         return std::make_shared<ResourceActor>( position, 0, sf::Vector2f{ 1.f, 1.f }, true, 1000,
                                                 Resources::Resource::ITEM_WOOD, Resources::ResourceSource::TREE, 20 );
      default:
         return nullptr;
   }
}
