//
// Created by dominik on 15.11.25.
//

#ifndef GAME1_INPUTACTIONS_H
#define GAME1_INPUTACTIONS_H

#include <functional>
#include <SFML/Window/Event.hpp>

struct InputActions
{
   std::function<void( const sf::Event& event )> onPress;
   std::function<void( const sf::Event& event )> onRelease;
};

#endif //GAME1_INPUTACTIONS_H
