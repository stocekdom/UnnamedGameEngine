//
// Created by dominik on 27.11.25.
//

#ifndef GAME1_INPUTCONTEXT_H
#define GAME1_INPUTCONTEXT_H

#include <unordered_map>
#include <SFML/Window/Event.hpp>
#include "InputEventKey.h"
#include "GameAction.h"

class InputContext
{
   public:
      GameAction getAction( const InputEventKey& inputEvent );

      void mapKey( sf::Keyboard::Key key, GameAction gameAction );

      void mapButton( sf::Mouse::Button button, GameAction gameAction );

      void mapMouseMove( GameAction gameAction );

      void mapMouseWheel( GameAction gameAction );

   private:
      std::unordered_map<InputEventKey, GameAction, InputEventKeyHash> actionsMap;
      bool consumesInput;
};

#endif //GAME1_INPUTCONTEXT_H
