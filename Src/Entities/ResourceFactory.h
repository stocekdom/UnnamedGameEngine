//
// Created by dominik on 16.12.25.
//

#ifndef GAME1_RESOURCEFACTORY_H
#define GAME1_RESOURCEFACTORY_H

#include "ResourceActor.h"
#include <memory>

class ResourceFactory
{
   public:
      static std::shared_ptr<ResourceActor> createResource( GameScene* scene, Resources::ResourceSource resource, const sf::Vector2f& position );
};
#endif //GAME1_RESOURCEFACTORY_H
