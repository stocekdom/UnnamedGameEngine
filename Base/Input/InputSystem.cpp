//
// Created by dominik on 15.11.25.
//
#include "InputSystem.h"
#include "Controller.h"
#include <vector>


void InputSystem::handleInput( sf::Event event )
{
   for( auto& controller: controllers )
      controller->handleInput( event );
}

void InputSystem::update( float dt )
{
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
