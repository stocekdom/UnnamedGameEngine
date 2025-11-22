#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include "ClickableText.h"

//
// Created by dominik on 18.11.25.
//
ClickableText::ClickableText( const std::string& fontPath, const std::string& inText, int size, sf::Color color,
                              sf::Vector2f position, float rotation, bool isVisible )
                              : UIElementText( fontPath, inText + " Unclicked", size, color, position, rotation, isVisible ), origText( inText )
{
}

bool ClickableText::onClick( const sf::Vector2f& position )
{
   auto bounds = text.getGlobalBounds();

   if(  bounds.contains( position ) )
   {
      clicked = !clicked;
      text.setString( origText + ( clicked ? " Clicked" : " Unclicked" ) );
      return true;
   }

   return UIElement::onClick( position );
}
