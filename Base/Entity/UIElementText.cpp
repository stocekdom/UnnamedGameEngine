#include <SFML/Graphics/Drawable.hpp>
#include "UIElementText.h"
#include "../Scene.h"

//
// Created by dominik on 15.10.25.
//

UIElementText::UIElementText( const std::string& fontPath, const std::string& inText, Mobility mobilityStatus, int size,
                              sf::Color color, sf::Vector2f position, float rotation, sf::Vector2f scale, bool isVisible )
      : UIElement( mobilityStatus, position, rotation, scale, isVisible ), isUIVisible( true )
{
   if( !font.loadFromFile( fontPath ) )
   {
      throw std::runtime_error( "Could not load font at " + fontPath );
   }

   text.setFont( font );
   text.setString( inText );
   text.setCharacterSize( size );
   text.setFillColor( color );
   isEntityDirty = true;
}

const sf::Drawable& UIElementText::getDrawable()
{
   return text;
}

void UIElementText::setText( std::string& newText )
{
   text.setString( newText );
}

void UIElementText::onStart( GameScene& scene, CollisionSystem& collisionSystem )
{
   scene.addEntityToScene( shared_from_this() );
}
