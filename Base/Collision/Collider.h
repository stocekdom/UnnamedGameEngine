//
// Created by dominik on 13.10.25.
//

#ifndef GAME1_COLLIDER_H
#define GAME1_COLLIDER_H

#include "Collidable.h"
#include "../Entity/SpacialEntity.h"
#include <memory>

class ColliderRect;

class ColliderPoint;

// Inherits from spacial since all colliders should be able to move around the world and be drawn
class Collider : public SpacialEntity
{
   public:

      explicit Collider( Collidable* owningActor, Mobility mobilityStatus, sf::Vector2f position = { 0, 0 }, float rotation = 0,
                         sf::Vector2f scale = { 1, 1 }, bool isVisible = false );

      void onStart( std::shared_ptr<GameContext>& context ) override;

      [[nodiscard]] bool isColliderEnabled() const;

      [[nodiscard]] const Collidable* getOwner() const;

      virtual void setIsEnabled( bool enabled );

      virtual void onCollision( const Collidable* other, CollisionInfo& info );

      // Colliders passed into test methods as raw pointers to avoid circular dependencies and since they are not owned by the actor
      virtual bool testCollision( const Collider* other, CollisionInfo& info ) const = 0;

      virtual bool testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const = 0;

      virtual bool testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const = 0;

   protected:
      bool isEnabled;
      // TODO try to rework with weak pointers
      Collidable* owner;
};

#endif //GAME1_COLLIDER_H
