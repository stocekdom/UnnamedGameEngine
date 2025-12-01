//
// Created by dominik on 01.12.25.
//
#include <SFML/System/Vector2.hpp>
#include "Math.h"

sf::Vector2f Math::parentRelativeToWorldPosition( const sf::Vector2f& parentPosition,
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