//
// Created by dominik on 23.11.25.
//
#include "UIRoot.h"

UIRoot::UIRoot( const std::shared_ptr<UIElement>& menuLayer )
      : UIElement( { 0.f, 0.f }, 0, { 1.0f, 1.0f }, false ), menuLayer( menuLayer )
{
}

void UIRoot::setMenuLayer( const std::shared_ptr<UIElement>& newMenuLayer )
{
   menuLayer = newMenuLayer;
}

void UIRoot::draw( sf::RenderTarget& target, const Renderer& renderer )
{
   if( menuLayer->isVisible() )
      menuLayer->draw( target, renderer );

   UIElement::draw( target, renderer );
}

bool UIRoot::onClick( const sf::Vector2f& position )
{
   // Only click the menu layer if it is visible (active) and dont propagate the signal further
   if( menuLayer->isVisible() )
   {
      menuLayer->onClick( position );
      return true;
   }

   return UIElement::onClick( position );
}

void UIRoot::onStart( std::shared_ptr<GameContext>& context )
{
   // Use lambda as wrappers for registering methods to events instead of using std::bind
   context->eventSystem->subscribe<GameResumed>( [this]( const GameResumed& event ) { onResumeGame( event ); } );
   context->eventSystem->subscribe<GamePaused>( [this]( const GamePaused& event ) { onPauseGame( event ); } );
   UIElement::onStart( context );
   menuLayer->onStart( context );
   menuLayer->setIsVisibleElement( false );
}

void UIRoot::onPauseGame( const GamePaused& event )
{
   menuLayer->setIsVisibleElement( true );
}

void UIRoot::onResumeGame( const GameResumed& event )
{
   menuLayer->setIsVisibleElement( false );
}

