//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_UIELEMENT_H
#define GAME1_UIELEMENT_H

#include "SpacialEntity.h"

class UIElement : public SpacialEntity
{
   public:
      UIElement( const sf::Vector2f& position, float rotation, const sf::Vector2f& scale, bool isVisible );
};
#endif //GAME1_UIELEMENT_H
