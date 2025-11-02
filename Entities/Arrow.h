//
// Created by dominik on 11.10.25.
//

#ifndef GAME1_ARROW_H
#define GAME1_ARROW_H

#include "../Base/Entity/Actor.h"
#include "../Base/Collision/Collidable.h"
#include "../Base/Collision/ColliderPoint.h"

// TODO make a projectile interface
class Arrow : public Actor, public Collidable
{
   public:
      // TODO This is bad passing this in constructor. Also using pointers to this if we need to construct a nested entity and pass this as a parent
      // Must implement ECS.
      explicit Arrow( const std::string& texturePath, sf::Vector2f position = { 0, 0 }, float rotation = 0, sf::Vector2f scale = { 1, 1 } );

      void init( GameScene& scene, CollisionSystem& collisionSystem ) override;

      void fire( sf::Vector2f initialVelocity );

      [[nodiscard]] bool isArrowFired() const;

      [[nodiscard]] bool hasArrowHitTarget() const;

      void tickFixed( float fixedDt ) override;

      void onCollision( const Collidable* other, CollisionInfo& info ) override;

   private:

      void createCollider();

      std::shared_ptr<ColliderPoint> collider;
      sf::Vector2f velocity;
      bool isFired = false;
      bool hasHitTarget = false;
};

#endif //GAME1_ARROW_H
