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

      void mapKeyAction( sf::Keyboard::Key key, GameAction gameAction );

      void mapKeyAxis( sf::Keyboard::Key key, GameAction gameAction );

      void mapButtonAction( sf::Mouse::Button button, GameAction gameAction );

      void mapButtonAxis( sf::Mouse::Button button, GameAction gameAction );

      void mapMouseMove( GameAction gameAction );

      void mapMouseWheel( GameAction gameAction );

   private:
      bool consumesInput = false;
      std::unordered_map<InputEventKey, GameAction, InputEventKeyHash> actionsMap;
};

#endif //GAME1_INPUTCONTEXT_H
