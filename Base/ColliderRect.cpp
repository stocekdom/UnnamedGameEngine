//
// Created by dominik on 13.10.25.
//
#include "ColliderRect.h"
#include "CollisionSystem.h"

ColliderRect::ColliderRect( sf::Vector2f position, sf::Vector2f extents, float rotation, Actor* owningActor ) : ICollider( owningActor, position ),
                                                                                                                halfExtents( extents / 2.0f ),
                                                                                                                rotation( rotation )
{
}

bool ColliderRect::testCollision( const ICollider* other, CollisionInfo& info ) const
{
   return other->testCollisionWithRectangle( this, info );
}

bool ColliderRect::testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const
{
   return CollisionSystem::pointRectangleCollisionHelper( other, this, info );
}

bool ColliderRect::testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const
{
   // TODO not implemented yet
   return false;
}

float ColliderRect::getRotation() const
{
   return rotation;
}

const sf::Vector2f& ColliderRect::getHalfExtents() const
{
   return halfExtents;
}

const sf::Vector2f& ColliderRect::getScale() const
{
   return scale;
}

void ColliderRect::setScale( const sf::Vector2f& inScale )
{
   scale = inScale;
}

void ColliderRect::setRotation( float inRotation )
{
   rotation = inRotation;
}

