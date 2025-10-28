//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_PLACABLEENTITY_H
#define GAME1_PLACABLEENTITY_H

#include "Entity.h"

class PlacableEntity : public Entity
{
   public:
      [[nodiscard]] virtual sf::Vector2f getPosition() const = 0;

      virtual void setPosition( const sf::Vector2f& newPosition ) = 0;
};
#endif //GAME1_PLACABLEENTITY_H
