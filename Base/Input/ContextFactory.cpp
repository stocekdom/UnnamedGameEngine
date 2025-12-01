//
// Created by dominik on 28.11.25.
//
#include "ContextFactory.h"

std::shared_ptr<InputContext> ContextFactory::createGameContext()
{
   auto context = std::make_shared<InputContext>();
   context->mapButton( sf::Mouse::Button::Left, GameAction::LEFT_CLICK );
   context->mapKey( sf::Keyboard::D, GameAction::CAMERA_MOVE_RIGHT );
   context->mapKey( sf::Keyboard::A, GameAction::CAMERA_MOVE_LEFT );
   context->mapKey( sf::Keyboard::W, GameAction::CAMERA_MOVE_UP );
   context->mapKey( sf::Keyboard::S, GameAction::CAMERA_MOVE_DOWN );
   context->mapMouseWheel( GameAction::CAMERA_ZOOM );
   return context;
}

std::shared_ptr<InputContext> ContextFactory::createMenuContext()
{
   auto context = std::make_shared<InputContext>();
   context->mapButton( sf::Mouse::Button::Left, GameAction::LEFT_CLICK );
   return context;
}

