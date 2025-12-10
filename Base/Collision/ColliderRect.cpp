//
// Created by dominik on 13.10.25.
//

#include "ColliderRect.h"
#include "CollisionHelper.h"

ColliderRect::ColliderRect( Mobility mobilityStatus, const sf::Vector2f& position, const sf::Vector2f& extents,
                            float rotation, Collidable* owningActor )
   : Collider( owningActor, mobilityStatus, position, rotation ), halfExtents( extents / 2.0f ), rotation( rotation )
{
   collider.setOutlineThickness( 1.5f );
   collider.setOutlineColor( sf::Color::Yellow );
   collider.setFillColor( sf::Color::Transparent );
   collider.setSize( extents );
   collider.setOrigin( halfExtents );
   isEntityDirty = true;
}

bool ColliderRect::testCollision( const Collider* other, CollisionInfo& info ) const
{
   return other->testCollisionWithRectangle( this, info );
}

bool ColliderRect::testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const
{
   return Collisions::pointRectangleCollisionHelper( other, this, info );
}

bool ColliderRect::testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const
{
   // TODO not implemented yet
   return false;
}

const sf::Vector2f& ColliderRect::getHalfExtents() const
{
   return halfExtents;
}

const sf::Drawable& ColliderRect::getDrawable()
{
   return collider;
}

void ColliderRect::tick( float deltaTime )
{
   if( isEntityDirty )
   {
      collider.setPosition( this->getPosition() );
      collider.setRotation( this->getRotation() );
      collider.setScale( this->getScale() );
      isEntityDirty = false;
   }
}
