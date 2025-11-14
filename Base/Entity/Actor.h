//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_ACTOR_H
#define GAME1_ACTOR_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "SpacialEntity.h"
#include "../Collision/CollisionInfo.h"

/**
 * Base class for all entities that can be drawn on the screen
 * Uses basic SFML sprite for drawing.
 * Provides all functionality for spacial information, ticking and sprite handling.
 * Provides necessary functionality for handling the sprite, spacial information, entity hierarchy and ticking
 * @warning Override the implemented methods at your own risk, or call them in the overridden methods.
 */
class Actor : public SpacialEntity
{
   public:
      explicit Actor( TextureManager& textureManager, const std::string& texturePath, sf::Vector2f position = { 0, 0 }, float rotation = 0,
                      sf::Vector2f scale = { 1, 1 }, bool isVisible = true );

      void init( GameScene& scene, CollisionSystem& collisionSystem ) override;

      void tick( float deltaTime ) override;

      void centerPivot();

      [[nodiscard]] sf::Vector2f getParentRelativePosition() const override;

      const sf::Drawable& getDrawable() override;

      virtual void setTexture( const sf::Texture& inTexture );

      virtual void setSprite( const sf::Sprite& sprite );

   protected:
      // TODO store textures in a central place
      sf::Texture texture;
      sf::Sprite sprite;
};

#endif //GAME1_ACTOR_H
