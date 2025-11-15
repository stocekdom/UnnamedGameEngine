//
// Created by dominik on 15.11.25.
//

#ifndef GAME1_CLICKABLE_H
#define GAME1_CLICKABLE_H

#include <SFML/System/Vector2.hpp>

class Clickable
{
   public:
      virtual void onClick( const sf::Vector2f& position ) = 0;
};
#endif //GAME1_CLICKABLE_H
