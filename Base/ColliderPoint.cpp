//
// Created by dominik on 13.10.25.
//
#include "ColliderPoint.h"
#include "CollisionSystem.h"

ColliderPoint::ColliderPoint( sf::Vector2f position, Actor* owningActor ) : ICollider( owningActor, position )
{
}

bool ColliderPoint::testCollision( const ICollider* other, CollisionInfo& info ) const
{
   return other->testCollisionWithPoint( this, info );
}

bool ColliderPoint::testCollisionWithPoint( const ColliderPoint* other, CollisionInfo& info ) const
{
   if( position != other->position )
      return false;

   info.localPoint = { 0, 0 };
   info.worldPoint = position;
   return true;
}

bool ColliderPoint::testCollisionWithRectangle( const ColliderRect* other, CollisionInfo& info ) const
{
   return CollisionSystem::pointRectangleCollisionHelper( this, other, info );
}
