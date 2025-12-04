//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_ACTOR_H
#define GAME1_ACTOR_H

#include "SpacialEntity.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

/**
 * Base class for all entities that can be drawn on the screen
 * Uses basic SFML sprite for drawing. Can be instantiated but doesn't have a texture for the sprite.
 * Provides all functionality for spacial information, ticking and sprite handling.
 * Provides necessary functionality for handling the sprite, spacial information, entity hierarchy and ticking
 * @warning Override the implemented methods at your own risk, or call them in the overridden methods.
 */
class Actor : public SpacialEntity
{
   public:
      explicit Actor( SpawnCategory spawnCategory, Mobility mobility, sf::Vector2f position = { 0, 0 }, float rotation = 0,
                      sf::Vector2f scale = { 1, 1 }, bool isVisible = true );

      void onStart( std::shared_ptr<GameContext>& context ) override;

      void tick( float deltaTime ) override;

      [[nodiscard]] SpawnCategory getSpawnCategory() const override;

      void setSpawnCategory( SpawnCategory newSpawnCategory ) override;

      void centerPivot();

      [[nodiscard]] sf::Vector2f getParentRelativePosition() const override;

      const sf::Drawable& getDrawable() override;

      virtual void setTexture( const sf::Texture& inTexture );

      virtual void setSprite( const sf::Sprite& sprite );

   protected:
      SpawnCategory spawnCategory;
      sf::Sprite sprite;
};

#endif //GAME1_ACTOR_H
