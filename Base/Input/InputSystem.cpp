//
// Created by dominik on 15.11.25.
//

#include "InputSystem.h"
#include "Controller.h"
#include <vector>

void InputSystem::handleInput( const sf::Event& event ) const
{
   // Always handle UI first
   if( uiController->handleInput( event ) )
      return;

   for( auto& controller: controllers )
      controller->handleInput( event );
}

void InputSystem::setUIController( std::unique_ptr<Controller> controller )
{
   uiController = std::move( controller );
}

void InputSystem::init( GameContext* context )
{
}

void InputSystem::onStart()
{
}

void InputSystem::update( float dt )
{
   uiController->tick( dt );

   for( auto& controller: controllers )
      controller->tick( dt );
}

void InputSystem::registerController( std::unique_ptr<Controller> controller )
{
   controllers.emplace_back( std::move( controller ) );
}

const std::vector<std::unique_ptr<Controller>>& InputSystem::getControllers() const
{
   return controllers;
}
