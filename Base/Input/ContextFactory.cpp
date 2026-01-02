//
// Created by dominik on 28.11.25.
//
#include "ContextFactory.h"

// TODO currently we're mapping axes to the same action and depend on value to determine direction. Better way?

std::shared_ptr<InputContext> ContextFactory::createGameContext()
{
   auto context = std::make_shared<InputContext>();
   context->mapButtonAction( sf::Mouse::Button::Left, GameAction::LEFT_CLICK );
   context->mapKeyAxis( sf::Keyboard::D, GameAction::CAMERA_MOVE_RIGHT );
   context->mapKeyAxis( sf::Keyboard::A, GameAction::CAMERA_MOVE_LEFT );
   context->mapKeyAxis( sf::Keyboard::W, GameAction::CAMERA_MOVE_UP );
   context->mapKeyAxis( sf::Keyboard::S, GameAction::CAMERA_MOVE_DOWN );
   context->mapMouseWheel( GameAction::CAMERA_ZOOM );
   return context;
}

std::shared_ptr<InputContext> ContextFactory::createPauseContext()
{
   // Empty context when the game is paused. Only UI is handled by UIController
   auto context = std::make_shared<InputContext>();
   return context;
}

std::shared_ptr<InputContext> ContextFactory::createBuildingPlacingContext()
{
   auto context = createGameContext();
   // Remap from game context
   context->mapButtonAction( sf::Mouse::Button::Left, GameAction::PLACE_BUILDING );
   context->mapMouseMove( GameAction::MOUSE_MOVE );
   return context;
}

std::shared_ptr<InputContext> ContextFactory::createUIControllerContext()
{
   auto context = std::make_shared<InputContext>();
   context->mapButtonAction( sf::Mouse::Button::Left, GameAction::LEFT_CLICK );
   return context;
}
