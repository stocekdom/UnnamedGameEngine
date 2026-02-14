//
// Created by dominik on 27.12.25.
//

#ifndef GAME1_SPRITECOMPONENT_H
#define GAME1_SPRITECOMPONENT_H

#include "SpriteMobility.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

struct SpriteComponent
{
   public:
      // Here the constructor is defined so that the derived classes can properly initialize the path, and we can also use parameter pack to initialize components (Args&&...)
      explicit SpriteComponent( std::string path, SpriteMobility mobility,
                                const sf::Vector2f& origin = { 0.f, 0.f } )
         : texturePath( std::move( path ) ), origin( origin ), mobility( mobility )
      {
      }

      virtual ~SpriteComponent() = default;

      std::string texturePath;

      [[nodiscard]] SpriteMobility getMobility() const
      {
         return mobility;
      }

      [[nodiscard]] const sf::FloatRect& getLocalBounds() const
      {
         return localBounds;
      }

      [[nodiscard]] const sf::FloatRect& getGlobalBounds() const
      {
         return globalBounds;
      }

      [[nodiscard]] const sf::Vector2f& getOrigin() const
      {
         return origin;
      }

      void setOrigin( const sf::Vector2f& newOrigin )
      {
         origin = newOrigin;
         originDirty = true;
      }

      [[nodiscard]] bool isOriginDirty() const
      {
         return originDirty;
      }

      void setDirty()
      {
         originDirty = true;
      }

      void setUndirty()
      {
         originDirty = false;
      }

   protected:
      /**
       * Global bounding rectangle of the sprite
       */
      sf::FloatRect globalBounds;
      sf::FloatRect localBounds;
      /**
       * Origin of the sprite, represented as a percentage of the sprite's dimensions.
       * For example, (0.5f, 0.5f) means the origin is in the middle of the sprite.
       * This is done because the sprite texture might not be loaded yet and we can't know its dimensions.
       */
      sf::Vector2f origin = { 0.f, 0.f };
      SpriteMobility mobility;
      bool originDirty = true;

      friend class SpriteSystem;
};
#endif //GAME1_SPRITECOMPONENT_H
