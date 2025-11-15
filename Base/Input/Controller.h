//
// Created by dominik on 09.10.25.
//

#ifndef GAME1_CONTROLLER_H
#define GAME1_CONTROLLER_H

#include <SFML/Window/Event.hpp>

class Controller
{
   public:
      virtual ~Controller() = default;

      virtual void handleInput( const sf::Event& event ) = 0;
};

#endif //GAME1_CONTROLLER_H
