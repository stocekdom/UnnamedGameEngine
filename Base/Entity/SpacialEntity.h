//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_SPACIALENTITY_H
#define GAME1_SPACIALENTITY_H

#include "PlacableEntity.h"

class SpacialEntity : public PlacableEntity
{
   public:
      [[nodiscard]] virtual sf::Vector2f getScale() const = 0;

      [[nodiscard]] virtual float getRotation() const = 0;

      virtual void setScale( const sf::Vector2f& newScale ) = 0;

      virtual void setRotation( float newRotation ) = 0;
};

#endif //GAME1_SPACIALENTITY_H
