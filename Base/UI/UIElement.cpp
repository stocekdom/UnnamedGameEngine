//
// Created by dominik on 01.11.25.
//
#include "UIElement.h"
#include "../Core/Math.h"

UIElement::UIElement( const sf::Vector2f& position, float rotation, bool isVisible ) : localPosition( position ),
                                                                                       localRotation( rotation ),
                                                                                       isVisibleElement( isVisible )
{
}

bool UIElement::isVisible() const
{
   return isVisibleElement;
}

sf::Vector2f UIElement::getPosition() const
{
   auto p = parent.lock();

   if( !p )
      return localPosition;

   return Math::PositionTransform::parentRelativeToWorldPosition( p->getPosition(),
                                                                  p->getRotation(),
                                                                  { 1.f, 1.f },
                                                                  localPosition );
}

float UIElement::getRotation() const
{
   auto p = parent.lock();

   if( !p )
      return localRotation;

   return localRotation + p->getRotation();
}

void UIElement::setIsVisibleElement( bool isVisible )
{
   isVisibleElement = isVisible;
}

void UIElement::addChild( const std::shared_ptr<UIElement>& child )
{
   children.push_back( child );
   child->setParent( shared_from_this() );
}

void UIElement::setParent( const std::shared_ptr<UIElement>& newParent )
{
   //newParent->addChild( shared_from_this() );
   parent = newParent;
}

void UIElement::move( const sf::Vector2f& offset )
{
   localPosition += offset;
}

void UIElement::rotate( float rotation )
{
   localRotation += rotation;
}

void UIElement::draw( sf::RenderTarget& target, const Renderer& renderer )
{
   for( auto& child: children )
      if( child->isVisible() )
         child->draw( target, renderer );
}

bool UIElement::onClick( const sf::Vector2f& position )
{
   return std::any_of( children.begin(), children.end(),
                       [&]( const std::shared_ptr<UIElement>& child ) { return child->onClick( position ); } );
}

