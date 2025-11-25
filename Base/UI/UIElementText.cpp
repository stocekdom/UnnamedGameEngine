#include <SFML/Graphics/Drawable.hpp>
#include "UIElementText.h"
#include "../Scene.h"

//
// Created by dominik on 15.10.25.
//

// TODO rework to onStart instead of constructor
UIElementText::UIElementText( const std::string& fontPath, const std::string& inText, int size, sf::Color color,
                              sf::Vector2f position, float rotation, bool isVisible )
      : UIElement( position, rotation, { 1.0f, 1.0f }, isVisible )
{
   if( !font.loadFromFile( fontPath ) )
   {
      throw std::runtime_error( "Could not load font at " + fontPath );
   }

   text.setFont( font );
   text.setString( inText );
   text.setCharacterSize( size );
   text.setFillColor( color );
   text.setPosition( position );
   text.setRotation( rotation );
}

void UIElementText::setText( std::string& newText )
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
