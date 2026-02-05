//
// Created by dominik on 15.11.25.
//
#include "Controller.h"

Controller::Controller( GameContext* context ) : gameContext( context )
{
}

bool Controller::handleInput( const sf::Event& event )
{
   // Initialization before switch to avoid compiler warning.
   GameAction action;

   // TODO lot of repeated code in keys and buttons.
   switch( event.type )
   {
      case sf::Event::KeyPressed:
         // Avoid repeated handling of the same key if it's held down.
         if( keyStates[ event.key.code ] )
            break;

         action = activeContext->getAction( { InputEventKey::Type::KeyboardPress, event.key.code } );
         keyStates[ event.key.code ] = true;
         return useAction( action, { 1.f } );

      case sf::Event::KeyReleased:
         keyStates[ event.key.code ] = false;
         action = activeContext->getAction( { InputEventKey::Type::KeyboardRelease, event.key.code } );
         return useAction( action, { 0.f } );

      case sf::Event::MouseButtonPressed:
         if( buttonStates[ event.mouseButton.button ] )
            break;

         buttonStates[ event.mouseButton.button ] = true;
         action = activeContext->getAction( { InputEventKey::Type::MouseButtonPress, event.mouseButton.button } );
         return useAction( action, { 1.f, { event.mouseButton.x, event.mouseButton.y } } );

      case sf::Event::MouseButtonReleased:
         buttonStates[ event.mouseButton.button ] = false;
         action = activeContext->getAction( { InputEventKey::Type::MouseButtonRelease, event.mouseButton.button } );
         return useAction( action, { 0.f, { event.mouseButton.x, event.mouseButton.y } } );

      case sf::Event::MouseMoved:
         action = activeContext->getAction( { InputEventKey::Type::MouseMove } );
         return useAction( action, { 0.f, { event.mouseMove.x, event.mouseMove.y } } );

      case sf::Event::MouseWheelScrolled:
         action = activeContext->getAction( { InputEventKey::Type::MouseWheel } );
         return useAction( action, { event.mouseWheelScroll.delta } );

      default:
         break;
   }

   return false;
}

bool Controller::useAction( GameAction action, const ActionData& data )
{
   if( actions.contains( action ) )
   {
      actions[ action ]( data );
      return true;
   }

   return false;
}
