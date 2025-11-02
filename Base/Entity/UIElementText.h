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
      UIElementText( const std::string& fontPath, const std::string& inText, int size = 16, sf::Color color = sf::Color::Black,
                     sf::Vector2f position = { 0, 0 }, float rotation = 0, sf::Vector2f scale = { 0, 0 }, bool isVisible = true );

      void init( GameScene& scene, CollisionSystem& collisionSystem ) override;

      const sf::Drawable& getDrawable() override;

      virtual void setText( std::string& newText );

   protected:
      bool isUIVisible;
      sf::Font font;
      sf::Text text;
};

#endif //GAME1_UIELEMENTTEXT_H
