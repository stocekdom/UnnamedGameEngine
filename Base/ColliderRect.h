//
// Created by dominik on 13.10.25.
//

#ifndef GAME1_COLLIDERRECT_H
#define GAME1_COLLIDERRECT_H

#include <SFML/System/Vector2.hpp>
#include "ICollider.h"

class ColliderRect : public ICollider
{
   public:
      // TODO pass sf::Vector2f by value in constructor if we use a reference in setPosition?
      ColliderRect( sf::Vector2f position, sf::Vector2f extents, float rotation, Actor* owningActor );

      [[nodiscard]] float getRotation() const;

      [[nodiscard]] const sf::Vector2f& getHalfExtents() const;

      [[nodiscard]] const sf::Vector2f& getScale() const;

      void setScale( const sf::Vector2f& scale );

      void setRotation( float rotation );

      bool testCollision( const ICollider* other, CollisionInfo& info ) const override;

      bool testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const override;

      bool testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const override;

   private:
      sf::Vector2f halfExtents;
      float rotation;
      sf::Vector2f scale;
};

#endif //GAME1_COLLIDERRECT_H
