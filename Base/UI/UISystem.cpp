//
// Created by dominik on 04.12.25.
//
#include "UISystem.h"
#include "UIElement.h"

UISystem::UISystem()
{
   // Empty root to avoid nullptr checks.
   uiRoot = std::make_shared<UIElement>( sf::Vector2f{ 0.f, 0.f }, 0, sf::Vector2f{ 0.f, 0.f }, false );
}

void UISystem::onStart( sf::RenderWindow& window, GameContext* context )
{
   uiRoot->onStart( context );
}

void UISystem::render( sf::RenderTarget& target, const Renderer& renderer ) const
{
   uiRoot->draw( target, renderer );
}

bool UISystem::onLeftClick( const sf::Vector2i& position ) const
{
   return uiRoot->onClick( sf::Vector2f{ position } );
}

void UISystem::addUiRootComponent( const std::shared_ptr<UIElement>& root )
{
   uiRoot = root;
}

void UISystem::attachToRoot( const std::shared_ptr<UIElement>& uiElement )
{
   //TODO
}
