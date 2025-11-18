//
// Created by dominik on 01.11.25.
//
#include "UIElement.h"

UIElement::UIElement( const sf::Vector2f& position, float rotation, bool isVisible ) : localPosition( position ),
                                                                                       localRotation( rotation ),
                                                                                       isVisibleElement( isVisible )
{
}

bool UIElement::isVisible() const
{
   return false;
}

sf::Vector2f UIElement::getPosition() const
{
   return sf::Vector2f();
}

float UIElement::getRotation() const
{
   return 0;
}

void UIElement::setIsVisibleElement( bool isVisible )
{
}

void UIElement::addChild( const std::shared_ptr<UIElement>& child )
{
}

void UIElement::move( const sf::Vector2f& offset )
{
}

void UIElement::rotate( float rotation )
{
}

