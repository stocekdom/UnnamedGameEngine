//
// Created by dominik on 13.10.25.
//

#ifndef GAME1_COLLIDERPOINT_H
#define GAME1_COLLIDERPOINT_H

#include "ICollider.h"

class ColliderPoint : public ICollider
{
   public:
      ColliderPoint( sf::Vector2f position, Actor* owningActor );

      bool testCollision( const ICollider* other, CollisionInfo& info ) const override;

      bool testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const override;

      bool testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const override;

   private:
};

#endif //GAME1_COLLIDERPOINT_H
