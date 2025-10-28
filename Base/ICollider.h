//
// Created by dominik on 13.10.25.
//

#ifndef GAME1_ICOLLIDER_H
#define GAME1_ICOLLIDER_H

#include <memory>
#include "Entity/Actor.h"
#include "CollisionInfo.h"

// Forward declarations to avoid circular dependencies
class ColliderRect;

class ColliderPoint;

// TODO inherit from placable or spacial entity
class ICollider
{
   public:

      ICollider( Actor* owningActor, sf::Vector2f position );

      [[nodiscard]] const sf::Vector2f& getPosition() const;

      [[nodiscard]] bool isColliderEnabled() const;

      [[nodiscard]] const Actor* getOwner() const;

      virtual void setIsEnabled( bool enabled );

      virtual void setPosition( const sf::Vector2f& newPosition );

      virtual void move( const sf::Vector2f& delta );

      virtual void onCollision( const Actor* other, CollisionInfo& info );

      // Colliders passed into test methods as raw pointers to avoid circular dependencies and since they are not owned by the actor
      virtual bool testCollision( const ICollider* other, CollisionInfo& info ) const = 0;

      virtual bool testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const = 0;

      virtual bool testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const = 0;

   protected:
      bool isEnabled;
      Actor* owner;
      sf::Vector2f position;
};

#endif //GAME1_ICOLLIDER_H
