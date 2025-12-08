//
// Created by dominik on 18.11.25.
//

#ifndef GAME1_CLICKABLETEXT_H
#define GAME1_CLICKABLETEXT_H

#include "../../Base/UI/UIElementText.h"

class ClickableText : public UIElementText
{
   public:
      ClickableText( const std::string& fontPath, const std::string& inText, int size = 16, sf::Color color = sf::Color::White,
                     sf::Vector2f position = { 0, 0 }, float rotation = 0, bool isVisible = true );

      bool onClick( const sf::Vector2f& position ) override;

   private:
      bool clicked = false;
      std::string origText;
};
#endif //GAME1_CLICKABLETEXT_H
