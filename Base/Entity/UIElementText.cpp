#include <SFML/Graphics/Drawable.hpp>
#include "UIElementText.h"

//
// Created by dominik on 15.10.25.
//

UIElementText::UIElementText( const std::string& fontPath, const std::string& inText, int size, sf::Color color, sf::Vector2f position, float rotation,
                              sf::Vector2f scale ) : rotation( rotation ), isUIVisible( true )
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
   text.setScale( scale );
}

const sf::Drawable& UIElementText::getDrawable()
{
   return text;
}

sf::Vector2f UIElementText::getPosition() const
{
   return text.getPosition();
}

void UIElementText::setPosition( const sf::Vector2f& newPosition )
{
   text.setPosition( newPosition );
}

sf::Vector2f UIElementText::getScale() const
{
   return text.getScale();
}

float UIElementText::getRotation() const
{
   return rotation;
}

void UIElementText::setScale( const sf::Vector2f& newScale )
{
   text.setScale( newScale );
}

void UIElementText::setRotation( float newRotation )
{
   text.setRotation( newRotation );
   rotation = newRotation;
}

void UIElementText::setText( std::string& newText )
{
   text.setString( newText );
}

void UIElementText::tickFixed( float fixedDt )
{
}

void UIElementText::tick( float deltaTime )
{
}

void UIElementText::setIsVisibleEntity( bool isVisibleEntity )
{
   isUIVisible = isVisibleEntity;
}

bool UIElementText::isVisible() const
{
   return isUIVisible;
}
