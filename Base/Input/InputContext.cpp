//
// Created by dominik on 27.11.25.
//
#include "InputContext.h"

GameAction InputContext::getAction( const InputEventKey& inputEvent )
{
   auto action = actionsMap.find( inputEvent );

   return action == actionsMap.end() ? GameAction::NONE : action->second;
}

void InputContext::mapKey( sf::Keyboard::Key key, GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::Keyboard, key } ] = gameAction;
}

void InputContext::mapButton( sf::Mouse::Button button, GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::MouseButton, button } ] = gameAction;
}

void InputContext::mapMouseMove( GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::MouseMove } ] = gameAction;
}

void InputContext::mapMouseWheel( GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::MouseWheel } ] = gameAction;
}

