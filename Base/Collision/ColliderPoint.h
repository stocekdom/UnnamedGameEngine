//
// Created by dominik on 13.10.25.
//

#ifndef GAME1_COLLIDERPOINT_H
#define GAME1_COLLIDERPOINT_H

#include <SFML/Graphics/CircleShape.hpp>
#include "ICollider.h"

class ColliderPoint : public ICollider
{
   public:
      ColliderPoint( const sf::Vector2f& position, Collidable* owningActor );

      void tick( float deltaTime ) override;

      const sf::Drawable& getDrawable() override;

      bool testCollision( const ICollider* other, CollisionInfo& info ) const override;

      bool testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const override;

      bool testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const override;

   private:
      sf::CircleShape collider;
      sf::Vector2f localPosition;
};

#endif //GAME1_COLLIDERPOINT_H
