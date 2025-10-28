//
// Created by dominik on 10.10.25.
//

#ifndef GAME1_TARGET_H
#define GAME1_TARGET_H

#include "../Base/Entity/Actor.h"
#include "../Base/ColliderRect.h"
#include "../Base/CollisionSystem.h"
#include "../Base/Observers/Subject.h"
#include <random>

class Target : public Actor, public Subject
{
   public:
      Target( const std::string& texturePath, CollisionSystem& system, sf::Vector2f position = { 0, 0 }, float rotation = 0, sf::Vector2f scale = { 1, 1 } );

      void setPosition( const sf::Vector2f& newPosition ) override;

      void setRotation( float newRotation ) override;

      void setScale( const sf::Vector2f& newScale ) override;

      void onCollision( const Actor* other, CollisionInfo& info ) override;

      void randomize( float maxHeight = 700, float minHeight = 100, float maxWidth = 1000, float minWidth = 1900, float maxRotation = 35,
                      float minRotation = -15, float maxScale = 1.6, float minScale = 1.2 );

   private:
      void createCollider( CollisionSystem& system );

      std::shared_ptr<ColliderRect> collider;
      std::mt19937 rng;
};

#endif //GAME1_TARGET_H
