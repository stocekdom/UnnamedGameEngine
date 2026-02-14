#include <SFML/Graphics/Drawable.hpp>
#include <utility>
#include "UIElementText.h"

//
// Created by dominik on 15.10.25.
//

UIElementText::UIElementText( std::string fontPath, const std::string& inText, int size, sf::Color color,
                              sf::Vector2f position, float rotation, bool isVisible )
      : UIElement( position, rotation, { 1.0f, 1.0f }, isVisible ), fontPath( std::move( fontPath ) )
{
   text.setString( inText );
   text.setCharacterSize( size );
   text.setFillColor( color );
}

void UIElementText::setText( const std::string& newText )
{
   text.setString( newText );
}

bool UIElementText::onClick( const sf::Vector2f& position )
{
   return UIElement::onClick( position );
}

void UIElementText::draw( sf::RenderTarget& target, const Renderer& renderer )
{
   renderer.render( text, target );
   UIElement::draw( target, renderer );
}

void UIElementText::onStart( GameContext* context )
{
   text.setFont( context->resourceManager->loadFont( fontPath ) );

   text.setPosition( getPosition() );
   text.setRotation( getRotation() );

   UIElement::onStart( context );
}
