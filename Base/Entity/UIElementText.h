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
      UIElementText( const std::string& fontPath, const std::string& inText, int size = 16, sf::Color color = sf::Color::Black, sf::Vector2f position = { 0, 0 }, float rotation = 0, sf::Vector2f scale = { 0, 0 } );

      const sf::Drawable& getDrawable() override;

      sf::Vector2f getPosition() const override;

      float getRotation() const override;

      sf::Vector2f getScale() const override;

      bool isVisible() const override;

      void setPosition( const sf::Vector2f& newPosition ) override;

      void setScale( const sf::Vector2f& newScale ) override;

      void setRotation( float newRotation ) override;

      void setIsVisibleEntity( bool isVisibleEntity ) override;

      void tickFixed( float fixedDt ) override;

      void tick( float deltaTime ) override;

      virtual void setText( std::string& newText );

   protected:
      bool isUIVisible;
      float rotation;
      sf::Font font;
      sf::Text text;
};

#endif //GAME1_UIELEMENTTEXT_H
