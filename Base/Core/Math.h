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

   class IsoSpace
   {
      public:
         inline static sf::Vector2f screenToWorldSpace( const sf::Vector2f& screenCoords )
         {
            return sf::Vector2f{ ( screenCoords.x + 2 * screenCoords.y ) / 4, ( 2 * screenCoords.y - screenCoords.x ) / 4 };
         }
   };

   class PositionTransform
   {
      public:
         static sf::Vector2f parentRelativeToWorldPosition( const sf::Vector2f& parentPosition,
                                                                   float parentRotation,
                                                                   const sf::Vector2f& parentScale,
                                                                   const sf::Vector2f& relativePosition )
         {
            auto angleCos = std::cos( parentRotation * Math::DEG_TO_RADIAN );
            auto angleSin = std::sin( parentRotation * Math::DEG_TO_RADIAN );

            auto rotatedX = relativePosition.x * angleCos - relativePosition.y * angleSin;
            auto rotatedY = relativePosition.x * angleSin + relativePosition.y * angleCos;

            return sf::Vector2f{ rotatedX * parentScale.x + parentPosition.x, rotatedY * parentScale.y + parentPosition.y };
         }
   };
}

#endif //GAME1_MATH_H
