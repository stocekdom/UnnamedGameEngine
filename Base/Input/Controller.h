//
// Created by dominik on 09.10.25.
//

#ifndef GAME1_CONTROLLER_H
#define GAME1_CONTROLLER_H

#include <SFML/Window/Event.hpp>
#include <functional>
#include "InputActions.h"

// TODO add input mappings and contexts in the future
/**
 * Basic controller providing a way to map keyboard and mouse events to functions.
 * Implements default input handling for keyboard and mouse events.
 * Concrete controllers shouldn't need to override this class and they should only define their mappings.
 */
class Controller
{
   public:
      Controller() = default;

      virtual ~Controller() = default;

      virtual void handleInput( const sf::Event& event );

   protected:
      void executeKeyboard( const sf::Event& event );

      void executeMouse( const sf::Event& event );

      // Uses std::function instead of a Command pattern for now since most of the time commands are just wrappers.
      std::unordered_map<sf::Keyboard::Key, InputActions> keyboardCommands;
      std::unordered_map<sf::Mouse::Button, InputActions> mouseCommands;
};

#endif //GAME1_CONTROLLER_H
