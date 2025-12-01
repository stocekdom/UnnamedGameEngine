//
// Created by dominik on 15.11.25.
//
#include "Controller.h"

void Controller::handleInput( const sf::Event& event )
{
   // Initialization before switch to avoid compiler warning.
   GameAction action;

   //std::cout << "Event: " << event.type << std::endl;
   // TODO lot of repeated code in keys and buttons.
   switch( event.type )
   {
      case sf::Event::KeyPressed:
         // Avoid repeated handling of the same key if it's held down.
         if( keyStates[ event.key.code ] )
            break;

         action = activeContext->getAction( { InputEventKey::Type::Keyboard, event.key.code } );
         keyStates[ event.key.code ] = true;

         if( actions.count( action ) )
            actions[ action ]( { true, 1.f } );

         break;

      case sf::Event::KeyReleased:
         keyStates[ event.key.code ] = false;
         action = activeContext->getAction( { InputEventKey::Type::Keyboard, event.key.code } );

         if( actions.count( action ) )
            actions[ action ]( { false, 0.f } );

         break;

      case sf::Event::MouseButtonPressed:
         if( buttonStates[ event.mouseButton.button ] )
            break;

         action = activeContext->getAction( { InputEventKey::Type::MouseButton, event.mouseButton.button } );
         keyStates[ event.mouseButton.button ] = true;

         if( actions.count( action ) )
            actions[ action ]( { true, 1.f, { event.mouseButton.x, event.mouseButton.y } } );

         break;

      case sf::Event::MouseButtonReleased:
         buttonStates[ event.mouseButton.button ] = false;
         action = activeContext->getAction( { InputEventKey::Type::MouseButton, event.mouseButton.button } );

         if( actions.count( action ) )
            actions[ action ]( { false, 0.f, { event.mouseButton.x, event.mouseButton.y} } );

         break;

      case sf::Event::MouseMoved:
         action = activeContext->getAction( { InputEventKey::Type::MouseMove } );

         if( actions.count( action ) )
            actions[ action ]( { false, 0.f, { event.mouseMove.x, event.mouseMove.y } } );

         break;

      case sf::Event::MouseWheelScrolled:
         action = activeContext->getAction( { InputEventKey::Type::MouseWheel } );

         if( actions.count( action ) )
            actions[ action ]( { false, event.mouseWheelScroll.delta } );

         break;

      default:
         break;
   }
}