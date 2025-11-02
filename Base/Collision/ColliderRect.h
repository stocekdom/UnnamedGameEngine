//
// Created by dominik on 13.10.25.
//

#ifndef GAME1_COLLIDERRECT_H
#define GAME1_COLLIDERRECT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ICollider.h"

class ColliderRect : public ICollider
{
   public:
      ColliderRect( const sf::Vector2f& position, const sf::Vector2f& extents, float rotation, Collidable* owningActor );

      [[nodiscard]] const sf::Vector2f& getHalfExtents() const;

      const sf::Drawable& getDrawable() override;

      void tick( float deltaTime ) override;

      bool testCollision( const ICollider* other, CollisionInfo& info ) const override;

      bool testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const override;

      bool testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const override;

   private:
      sf::RectangleShape collider;
      sf::Vector2f halfExtents;
      float rotation;
      sf::Vector2f scale;
};

#endif //GAME1_COLLIDERRECT_H
