//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_UIELEMENTTEXT_H
#define GAME1_UIELEMENTTEXT_H

#include <SFML/Graphics/Text.hpp>
#include "UIElement.h"

class UIElementText : public UIElement
{
   public:
      UIElementText( std::string fontPath, const std::string& inText, int size = 16, sf::Color color = sf::Color::White,
                     sf::Vector2f position = { 0, 0 }, float rotation = 0, bool isVisible = true );

      virtual void setText( const std::string& newText );

      void onStart( GameContext* context ) override;

      bool onClick( const sf::Vector2f& position ) override;

      void draw( sf::RenderTarget& target, const Renderer& renderer ) override;

   protected:
      std::string fontPath;
      sf::Text text;
};

#endif //GAME1_UIELEMENTTEXT_H
