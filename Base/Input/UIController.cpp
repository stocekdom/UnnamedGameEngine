//
// Created by dominik on 02.01.26.
//

#include "UIController.h"

UIController::UIController( GameContext* context ) : Controller( context )
{
}

bool UIController::handleInput( const sf::Event& event )
{
   if( event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left )
      return onLeftClick( sf::Vector2i( event.mouseButton.x, event.mouseButton.y ) );

   return false;
}

void UIController::tick( float dt )
{
}

bool UIController::onLeftClick( const sf::Vector2i& position ) const
{
   return gameContext->uiSystem->onLeftClick( position );
}
