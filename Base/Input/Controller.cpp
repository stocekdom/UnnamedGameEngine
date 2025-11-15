//
// Created by dominik on 15.11.25.
//
#include "Controller.h"

void Controller::handleInput( const sf::Event& event )
{
   if( event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased )
   {
      executeKeyboard( event );
   }
   else if( event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased )
   {
      executeMouse( event );
   }
}

// TODO try to generalize this. Currently we repeat code

void Controller::executeKeyboard( const sf::Event& event )
{
   auto it = keyboardCommands.find( event.key.code );

   if( it == keyboardCommands.end() )
      return;

   if( event.type == sf::Event::KeyPressed )
   {
      if( it->second.onPress )
         it->second.onPress( event );
   }
   else if( event.type == sf::Event::KeyReleased )
   {
      if( it->second.onRelease )
         it->second.onRelease( event );
   }
}

void Controller::executeMouse( const sf::Event& event )
{
   auto it = mouseCommands.find( event.mouseButton.button );

   if( it == mouseCommands.end() )
      return;

   if( event.type == sf::Event::MouseButtonPressed )
   {
      if( it->second.onPress )
         it->second.onPress( event );
   }
   else if( event.type == sf::Event::MouseButtonReleased )
   {
      if( it->second.onRelease )
         it->second.onRelease( event );
   }
}

