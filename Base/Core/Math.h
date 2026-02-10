//
// Created by dominik on 28.10.25.
//

#ifndef GAME1_MATH_H
#define GAME1_MATH_H

#include "../GameMap/TileTypes.h"
#include <SFML/System/Vector2.hpp>
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
      // Offset from the tile center where the building's pivot should be, assuming the building's pivot is correctly placed at the bottom center point
      const static constexpr float BUILDING_TILE_CENTER_Y_OFFSET = ( SPRITE_HEIGHT / 2 ) * 0.9f;
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

   inline sf::Vector2f worldToScreenSpace( const sf::Vector2f& worldCoords )
   {
      return sf::Vector2f{ 2 * worldCoords.x - 2 * worldCoords.y, worldCoords.x + worldCoords.y };
   }

   /**
    * Returns a index of a game map based on coordinates. The map works as a matrix, and the X is a row index. The tiles are numbered by rows
    * @note Indexing a map is different from indexing screen coordinates, where the row is a Y coordinate
    * @param x Row index
    * @param y Column index
    * @param width Map width
    * @return The 1D array index
    */
   inline int coordsToIndex( int x, int y, int width )
   {
      return y + x * width;
   }

   inline TileIndex indexToCoords( int index, int width )
   {
      return { index / width, index % width };
   }

   sf::Vector2f parentRelativeToWorldPosition( const sf::Vector2f& parentPosition,
                                               float parentRotation,
                                               const sf::Vector2f& parentScale,
                                               const sf::Vector2f& relativePosition );
};

#endif //GAME1_MATH_H
