#include <vector>
#include "InputSystem.h"

//
// Created by dominik on 15.11.25.
//
void InputSystem::registerController( std::unique_ptr<Controller> controller )
{
   controllers.emplace_back( std::move( controller ) );
}

const std::vector<std::unique_ptr<Controller>>& InputSystem::getControllers() const
{
   return controllers;
}

void InputSystem::handleInput( sf::Event event )
{
   for( auto& controller: controllers )
   {
      controller->handleInput( event );
   }
}
