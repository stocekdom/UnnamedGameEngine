//
// Created by dominik on 27.11.25.
//
#include "InputContext.h"

GameAction InputContext::getAction( const InputEventKey& inputEvent )
{
   auto action = actionsMap.find( inputEvent );

   return action == actionsMap.end() ? GameAction::NO_ACTION : action->second;
}

void InputContext::mapKeyAction( sf::Keyboard::Key key, GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::KeyboardPress, key } ] = gameAction;
}

void InputContext::mapKeyAxis( sf::Keyboard::Key key, GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::KeyboardPress, key } ] = gameAction;
   actionsMap[ { InputEventKey::Type::KeyboardRelease, key } ] = gameAction;
}

void InputContext::mapButtonAction( sf::Mouse::Button button, GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::MouseButtonPress, button } ] = gameAction;
}

void InputContext::mapButtonAxis( sf::Mouse::Button button, GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::MouseButtonPress, button } ] = gameAction;
   actionsMap[ { InputEventKey::Type::MouseButtonRelease, button } ] = gameAction;
}

void InputContext::mapMouseMove( GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::MouseMove } ] = gameAction;
}

void InputContext::mapMouseWheel( GameAction gameAction )
{
   actionsMap[ { InputEventKey::Type::MouseWheel } ] = gameAction;
}
