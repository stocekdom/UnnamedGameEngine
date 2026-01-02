//
// Created by dominik on 09.10.25.
//

#ifndef GAME1_CONTROLLER_H
#define GAME1_CONTROLLER_H

#include "InputContext.h"
#include "../GameContext.h"
#include <SFML/Window/Event.hpp>
#include <functional>
#include <memory>

/**
 * Basic controller providing a way to map keyboard and mouse events to functions with support for different contexts.
 * Implements default input handling for keyboard and mouse events.
 * Concrete controllers shouldn't need to override this class, and they should only define their mappings.
 */
class Controller
{
   public:
      Controller( GameContext* context );

      virtual ~Controller() = default;

      virtual void tick( float dt ) = 0;

      /**
       * The main method that is called to handle a polled event.
       * The default implementation already handles getting an action from active context, key and mouse button states and calling an action callback
       * @warning Override only in rare cases when you need to handle the event differently tha by using game actions and callbacks
       * @param event The polled event data
       * @return Returns true if the input has been successfully handled
       */
      virtual bool handleInput( const sf::Event& event );

   protected:
      // TODO context stack so we dont have to repeat actions in contexts and contexts defines its specific actions and if the input falls through
      std::shared_ptr<InputContext> activeContext;
      GameContext* gameContext;

      // Uses std::function instead of a Command pattern for now since most of the time commands are just wrappers.
      std::unordered_map<GameAction, std::function<void( const ActionData& data )>> actions;

   private:
      // TODO better way? Array or bitmap?
      bool keyStates[ sf::Keyboard::Key::KeyCount ]{};
      bool buttonStates[ sf::Mouse::Button::ButtonCount ]{};

      bool useAction( GameAction action, const ActionData& data );
};

#endif //GAME1_CONTROLLER_H
