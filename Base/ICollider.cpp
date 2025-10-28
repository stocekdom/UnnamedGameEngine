//
// Created by dominik on 13.10.25.
//
#include "ICollider.h"

ICollider::ICollider( Actor* owningActor, sf::Vector2f position ) : owner( owningActor ), position( position ), isEnabled( true )
{
}

const sf::Vector2f& ICollider::getPosition() const
{
   return position;
}

void ICollider::setPosition( const sf::Vector2f& newPosition )
{
   position = newPosition;
}

const Actor* ICollider::getOwner() const
{
   return owner;
}

void ICollider::onCollision( const Actor* other, CollisionInfo& info )
{
   if( owner != nullptr )
   {
      owner->onCollision( other, info );
   }
}

void ICollider::move( const sf::Vector2f& delta )
{
   position += delta;
}

bool ICollider::isColliderEnabled() const
{
   return isEnabled;
}

void ICollider::setIsEnabled( bool enabled )
{
   isEnabled = enabled;
}
