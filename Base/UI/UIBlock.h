//
// Created by dominik on 18.11.25.
//

#ifndef GAME1_UIBLOCK_H
#define GAME1_UIBLOCK_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "UIElement.h"

class UIBlock : public UIElement
{
   public:
      explicit UIBlock( const sf::Vector2f& extents, sf::Color fillColor = sf::Color::Blue,
                        const sf::Vector2f& position = { 0.f, 0.f },
                        float rotation = 0, bool isVisible = true );

      bool onClick( const sf::Vector2f& position ) override;

      void draw( sf::RenderTarget& target, const Renderer& renderer ) override;

   protected:
      sf::RectangleShape block;
};

#endif //GAME1_UIBLOCK_H
