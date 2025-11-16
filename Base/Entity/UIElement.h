//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_UIELEMENT_H
#define GAME1_UIELEMENT_H

#include "SpacialEntity.h"

/**
 * Base class for all UI elements
 * Doesnt provide any component that will get drawn. It's up to the derived classes to implement how they will get drawn
 */
class UIElement : public SpacialEntity
{
   public:
      UIElement( Mobility mobilityStatus, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale, bool isVisible );
};
#endif //GAME1_UIELEMENT_H
