//
// Created by dominik on 28.10.25.
//

#ifndef GAME1_MATH_H
#define GAME1_MATH_H

namespace Math
{
   const static constexpr float DEG_TO_RADIAN = 0.0174532925f;
   const static constexpr float GRAVITY = 9.81f;
   const static constexpr float RADIAN_TO_DEG = 57.2957795;
   const static constexpr float PIXELS_PER_METER = 40.0f;

   class IsoSpace
   {
      public:
         static sf::Vector2f screenToWorldSpace( const sf::Vector2f& screenCoords )
         {
            return sf::Vector2f{ ( screenCoords.x + 2 * screenCoords.y ) / 4, ( 2 * screenCoords.y - screenCoords.x ) / 4 };
         }
   };
}

#endif //GAME1_MATH_H
