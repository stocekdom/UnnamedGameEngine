//
// Created by dominik on 13.10.25.
//
#include "ColliderPoint.h"
#include "CollisionHelper.h"

ColliderPoint::ColliderPoint( Mobility mobilityStatus, const sf::Vector2f& position, Collidable* owningActor )
   : Collider( owningActor, mobilityStatus, position )
{
   collider.setFillColor( sf::Color::Yellow );
   collider.setRadius( 2.0f );
   collider.setOrigin( { collider.getRadius() / 2, collider.getRadius() / 2 } );
   isEntityDirty = true;
}

bool ColliderPoint::testCollision( const Collider* other, CollisionInfo& info ) const
{
   return other->testCollisionWithPoint( this, info );
}

bool ColliderPoint::testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const
{
   return Collisions::pointPointCollisionHelper( this, other, info );
}

bool ColliderPoint::testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const
{
   return Collisions::pointRectangleCollisionHelper( this, other, info );
}

const sf::Drawable& ColliderPoint::getDrawable()
{
   return collider;
}

void ColliderPoint::tick( float deltaTime )
{
   if( isEntityDirty )
   {
      collider.setPosition( this->getPosition() );
      isEntityDirty = false;
   }
}
