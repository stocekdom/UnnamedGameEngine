//
// Created by dominik on 11.10.25.
//

#ifndef GAME1_ARROW_H
#define GAME1_ARROW_H

#include "../Base/Entity/Actor.h"
#include "../Base/CollisionSystem.h"

// TODO make a projectile interface
class Arrow : public Actor
{
   public:
      // TODO review how to get Collision system in a better way
      Arrow( const std::string& texturePath, CollisionSystem& system, sf::Vector2f position = { 0, 0 }, float rotation = 0,
             sf::Vector2f scale = { 1, 1 } );

      void fire( sf::Vector2f initialVelocity );

      [[nodiscard]] bool isArrowFired() const;

      [[nodiscard]] bool hasArrowHitTarget() const;

      void tickFixed( float fixedDt ) override;

      void onCollision( const Actor* other, CollisionInfo& info ) override;

      // TODO big pain also having to modify the collider in these functions. Store the collider in localspace. components, trees?
      void setRotation( float inRotation ) override;

      void setPosition( const sf::Vector2f& position ) override;

      void setScale( const sf::Vector2f& scale ) override;

   private:

      void createCollider( CollisionSystem& system );

      std::shared_ptr<ColliderPoint> collider;
      // TODO store gravity and conversions in a central place
      const static constexpr float GRAVITY = 9.81f;
      const static constexpr float RADIAN_TO_DEG = 57.2957795;
      const static constexpr float PIXELS_PER_METER = 40.0f;
      sf::Vector2f velocity;
      bool isFired = false;
      bool hasHitTarget = false;
};

#endif //GAME1_ARROW_H
