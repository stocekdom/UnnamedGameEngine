//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_ACTOR_H
#define GAME1_ACTOR_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../CollisionInfo.h"
#include "SpacialEntity.h"

class Actor : public SpacialEntity
{
   public:
      explicit Actor( const std::string& texturePath, sf::Vector2f position = { 0, 0 }, float rotation = 0, sf::Vector2f scale = { 1, 1 } );

      virtual ~Actor() = default;

      // TODO review if this is the best option to handle collisions. Also should implement a collidable interface.
      virtual void onCollision( const Actor* other, CollisionInfo& info );

      // Tick with fixed time passed between frames. Usage: Simulation, physics, etc.
      void tickFixed( float fixedDt ) override;

      // Tick with actual time passed between frames. Usage: Rendering, UI, Real time events, etc.
      void tick( float deltaTime ) override;

      void centerPivot();

      [[nodiscard]] sf::Vector2f getPosition() const override;

      [[nodiscard]] float getRotation() const override;

      [[nodiscard]] sf::Vector2f getScale() const override;

      const sf::Drawable& getDrawable() override;

      bool isVisible() const override;

      virtual void setTexture( const sf::Texture& inTexture );

      virtual void setSprite( const sf::Sprite& sprite );

      void setPosition( const sf::Vector2f& newPosition ) override;

      void setRotation( float newRotation ) override;

      void setScale( const sf::Vector2f& scale ) override;

      void setIsVisibleEntity( bool isVisibleEntity ) override;

   protected:

      // Storing rotation like this since SFML returns only rotation in 0-360 range.
      float rotation;
      // TODO store textures in a central place
      sf::Texture texture;
      sf::Sprite sprite;
      bool isVisibleActor;
};

#endif //GAME1_ACTOR_H
