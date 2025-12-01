//
// Created by dominik on 28.10.25.
//

#ifndef GAME1_MATH_H
#define GAME1_MATH_H

#include <cmath>

namespace Math
{
   const static constexpr float DEG_TO_RADIAN = 0.0174532925f;
   const static constexpr float GRAVITY = 9.81f;
   const static constexpr float RADIAN_TO_DEG = 57.2957795;
   const static constexpr float PIXELS_PER_METER = 40.0f;

   namespace IsometricConstants
   {
      // These values only work for dimetric projection. If you need any other projection (true isometric), you'll have to recalculate them.
      const static constexpr float SPRITE_WIDTH = 256;
      const static constexpr float SPRITE_HEIGHT = SPRITE_WIDTH / 2;
      // The width of the original square in the world grid
      const static constexpr float WORLD_TILE_WIDTH = SPRITE_WIDTH / 4;
   }

   inline sf::Vector2f normalize( const sf::Vector2f& vector )
   {
      float magnitude = vector.x * vector.x + vector.y * vector.y;

      // Handle zero vector (cannot divide by zero)
      // Check against a small tolerance (epsilon) instead of 0.0f
      if( magnitude <= std::numeric_limits<float>::epsilon() )
         return { 0.0f, 0.0f };

      magnitude = std::sqrt( magnitude );
      return { vector.x / magnitude, vector.y / magnitude };
   }

   inline sf::Vector2f screenToWorldSpace( const sf::Vector2f& screenCoords )
   {
      return sf::Vector2f{ ( screenCoords.x + 2 * screenCoords.y ) / 4, ( 2 * screenCoords.y - screenCoords.x ) / 4 };
   }

   sf::Vector2f parentRelativeToWorldPosition( const sf::Vector2f& parentPosition,
                                               float parentRotation,
                                               const sf::Vector2f& parentScale,
                                               const sf::Vector2f& relativePosition );
};

#endif //GAME1_MATH_H
