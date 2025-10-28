//
// Created by dominik on 09.10.25.
//
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <memory>
#include "BowController.h"
#include "Commands/BowCommands.h"

void BowController::handleInput( const sf::Event& event )
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

BowController::BowController( const std::shared_ptr<Bow>& bow ) : pawn( bow )
{
   keyboardCommands[ sf::Keyboard::S ] = std::make_unique<RotateUp>( bow );
   keyboardCommands[ sf::Keyboard::W ] = std::make_unique<RotateDown>( bow );
   mouseCommands[ sf::Mouse::Left ] = std::make_unique<Charging>( bow );
}

void BowController::executeKeyboard( sf::Event event )
{
   auto it = keyboardCommands.find( event.key.code );

   if( it == keyboardCommands.end() )
      return;

   if( event.type == sf::Event::KeyPressed )
   {
      it->second->execute();
   }
   else if( event.type == sf::Event::KeyReleased )
   {
      it->second->stop();
   }
}

void BowController::executeMouse( sf::Event event )
{
   auto it = mouseCommands.find( event.mouseButton.button );

   if( it == mouseCommands.end() )
      return;

   if( event.type == sf::Event::MouseButtonPressed )
   {
      it->second->execute();
   }
   else if( event.type == sf::Event::MouseButtonReleased )
   {
      it->second->stop();
   }
}
