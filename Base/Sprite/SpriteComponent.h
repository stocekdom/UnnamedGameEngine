//
// Created by dominik on 27.12.25.
//

#ifndef GAME1_SPRITECOMPONENT_H
#define GAME1_SPRITECOMPONENT_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

#include "SpriteMobility.h"

struct SpriteComponent
{
   public:
      // Here the constructor is defined so that the derived classes can properly initialize the path, and we can also use parameter pack to initialize components (Args&&...)
      explicit SpriteComponent( std::string path, SpriteMobility mobility ) : texturePath( std::move( path ) ), mobility( mobility )
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
      sf::Vector2f origin = { 0.f, 0.f };
      SpriteMobility mobility;
      bool originDirty = true;

      friend class SpriteSystem;
};
#endif //GAME1_SPRITECOMPONENT_H
