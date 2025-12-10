//
// Created by dominik on 01.11.25.
//

#ifndef GAME1_COLLIDABLE_H
#define GAME1_COLLIDABLE_H

#include "CollisionInfo.h"

/**
 * An interface for entities that can be collided with
 * Provides a default implementation for collider storage and registering
 */
class Collidable
{
   public:
      virtual ~Collidable() = default;

      virtual void onCollision( const Collidable* other, CollisionInfo& info ) = 0;
};
#endif //GAME1_COLLIDABLE_H
