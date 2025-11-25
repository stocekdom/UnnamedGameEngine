#include "SpacialEntity.h"
#include "../Core/Math.h"
#include <SFML/System/Vector2.hpp>
#include <valarray>

//
// Created by dominik on 31.10.25.
//
SpacialEntity::SpacialEntity( Mobility mobilityStatus, const sf::Vector2f& position, float rotation,
                              const sf::Vector2f& scale, bool isVisible )
      : mobility( mobilityStatus ), isVisibleEntity( isVisible ), localPosition( position ), localRotation( rotation ),
        localScale( scale )
{
}

sf::Vector2f SpacialEntity::getPosition() const
{
   auto p = parent.lock();

   if( !p )
      return localPosition;

   return Math::PositionTransform::parentRelativeToWorldPosition( p->getPosition(),
                                                                  p->getRotation(),
                                                                  p->getScale(),
                                                                  localPosition );
}

sf::Vector2f SpacialEntity::getParentRelativePosition() const
{
   return localPosition;
}

sf::Vector2f SpacialEntity::getScale() const
{
   auto p = parent.lock();

   if( !p )
      return localScale;

   // sf::Vector2f
   auto pScale = p->getScale();
   return { localScale.x * pScale.x, localScale.y * pScale.y };
}

float SpacialEntity::getRotation() const
{
   auto p = parent.lock();

   if( !p )
      return localRotation;

   return localRotation + p->getRotation();
}

bool SpacialEntity::isVisible() const
{
   return isVisibleEntity;
}

void SpacialEntity::setIsVisibleEntity( bool isVisible )
{
   isVisibleEntity = isVisible;
}

void SpacialEntity::setPosition( const sf::Vector2f& newPosition )
{
   localPosition = newPosition;
   setDirty();
}

void SpacialEntity::setScale( const sf::Vector2f& newScale )
{
   localScale = newScale;
   setDirty();
}

void SpacialEntity::setRotation( float newRotation )
{
   localRotation = newRotation;
   setDirty();
}

void SpacialEntity::move( const sf::Vector2f& offset )
{
   localPosition += offset;
   setDirty();
}

void SpacialEntity::rotate( float rotation )
{
   localRotation += rotation;
   setDirty();
}

void SpacialEntity::scale( const sf::Vector2f& scale )
{
   localScale.x *= scale.x;
   localScale.y *= scale.y;
   setDirty();
}

void SpacialEntity::tickFixed( float fixedDt )
{
}

void SpacialEntity::tick( float deltaTime )
{
}

Mobility SpacialEntity::getMobility() const
{
   return mobility;
}
