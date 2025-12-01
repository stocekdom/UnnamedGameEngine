//
// Created by dominik on 09.10.25.
//

#ifndef GAME1_CONTROLLER_H
#define GAME1_CONTROLLER_H

#include <SFML/Window/Event.hpp>
#include "InputContext.h"
#include <functional>
#include <memory>

/**
 * Basic controller providing a way to map keyboard and mouse events to functions with support for different contexts.
 * Implements default input handling for keyboard and mouse events.
 * Concrete controllers shouldn't need to override this class and they should only define their mappings.
 */
class Controller
{
   public:
      Controller() = default;

      virtual ~Controller() = default;

      virtual void tick( float dt ) = 0;

      void handleInput( const sf::Event& event );

   protected:
      std::shared_ptr<InputContext> activeContext;

      // Uses std::function instead of a Command pattern for now since most of the time commands are just wrappers.
      std::unordered_map<GameAction, std::function<void( const ActionData& data )>> actions;

   private:
      bool keyStates[sf::Keyboard::Key::KeyCount]{};
      bool buttonStates[sf::Mouse::Button::ButtonCount]{};
};

#endif //GAME1_CONTROLLER_H
