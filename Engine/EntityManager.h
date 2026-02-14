//
// Created by dominik on 20.12.25.
//

#ifndef GAME1_ENTITYMANAGER_H
#define GAME1_ENTITYMANAGER_H

#include <queue>

#include "Entity.h"

class EntityManager
{
   public:
      EntityManager();

      Entity createEntity();

      bool deleteEntity( Entity entity );

      bool exists( Entity entity );

   private:
      std::deque<Entity> availableEntityIds;
      Entity lastCreatedEntityId = INVALID_ENTITY;
      Entity livingEntitiesCount = 0;
};

#endif //GAME1_ENTITYMANAGER_H
