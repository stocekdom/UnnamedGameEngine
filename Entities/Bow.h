//
// Created by dominik on 09.10.25.
//

#ifndef GAME1_BOW_H
#define GAME1_BOW_H

#include <memory>
#include "../Base/Entity/Actor.h"
#include "Arrow.h"

class Bow : public Actor
{
   public:
      explicit Bow( const std::string& texturePath, sf::Vector2f position = { 0, 0 }, float rotation = 0, sf::Vector2f scale = { 1, 1 } );

      void init( GameScene& scene, CollisionSystem& collisionSystem ) override;

      void charge( float speed );

      void setRotationSpeed( float rotation );

      void fire();

      void tick( float deltaTime ) override;

   private:
      std::weak_ptr<Arrow> arrow;
      float rotationSpeed = 0;
      float chargeSpeed = 0;
      float chargeLevel = 0;
      const static constexpr float MAX_CHARGE = 40;
      const static constexpr float MAX_ANGLE = 60;
};

#endif //GAME1_BOW_H
