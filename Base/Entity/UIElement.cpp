//
// Created by dominik on 01.11.25.
//
#include "UIElement.h"

UIElement::UIElement( Mobility mobilityStatus, const sf::Vector2f& position, float rotation,
                      const sf::Vector2f& scale, bool isVisible )
      : SpacialEntity( mobilityStatus, position, rotation, scale, isVisible )
{
}

