//
// Created by dominik on 18.11.25.
//
#include "UIBlock.h"

UIBlock::UIBlock( const sf::Vector2f& extents, sf::Color fillColor, const sf::Vector2f& position, float rotation, bool isVisible )
      : UIElement( position, rotation, isVisible )
{
   block.setSize( extents );
   block.setFillColor( fillColor );
   block.setPosition( position );
   block.setRotation( rotation );
}

bool UIBlock::onClick( const sf::Vector2f& position )
{
   return UIElement::onClick( position );
}

void UIBlock::draw( sf::RenderTarget& target, const Renderer& renderer )
{
   renderer.render( block, target );
   UIElement::draw( target, renderer );
}

