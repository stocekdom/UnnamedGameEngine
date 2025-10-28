//
// Created by dominik on 13.10.25.
//
#include <cmath>
#include "CollisionSystem.h"
#include "ColliderPoint.h"
#include "ColliderRect.h"

void CollisionSystem::registerCollider( const std::shared_ptr<ICollider>& collider )
{
   colliders.push_back( collider );
}

const std::vector<std::weak_ptr<ICollider>>& CollisionSystem::getColliders() const
{
   return colliders;
}

void CollisionSystem::update( float dt )
{
   for( int i = 0; i < colliders.size(); ++i )
   {
      auto a = colliders[ i ].lock();
      if( !a )
         continue;

      if( !a->isColliderEnabled() )
         continue;

      for( int j = i + 1; j < colliders.size(); ++j )
      {
         auto b = colliders[ j ].lock();
         if( !b )
            continue;

         if( !b->isColliderEnabled() )
            continue;

         CollisionInfo info;

         if( a->testCollision( b.get(), info ) )
         {
            a->onCollision( b->getOwner(), info );
            b->onCollision( a->getOwner(), info );
         }
      }
   }
}

bool CollisionSystem::pointRectangleCollisionHelper( const ColliderPoint* point, const ColliderRect* rect, CollisionInfo& info )
{
   sf::Vector2f pointToRectLocalSpace = point->getPosition() - rect->getPosition();
   float rectRotationSin = std::sin( -rect->getRotation() );
   float rectRotationCos = std::cos( -rect->getRotation() );

   // Rotate point to be axis aligned with rectangle
   // https://danceswithcode.net/engineeringnotes/rotations_in_2d/rotations_in_2d.html
   pointToRectLocalSpace.x = rectRotationCos * pointToRectLocalSpace.x - rectRotationSin * pointToRectLocalSpace.y;
   pointToRectLocalSpace.y = rectRotationSin * pointToRectLocalSpace.x + rectRotationCos * pointToRectLocalSpace.y;

   // Detect if the point is within the rectangle bounds
   if( std::abs( pointToRectLocalSpace.x ) <= ( rect->getHalfExtents().x * rect->getScale().x ) &&
       std::abs( pointToRectLocalSpace.y ) <= ( rect->getHalfExtents().y * rect->getScale().y ) )
   {
      info.worldPoint = point->getPosition();
      info.localPoint = pointToRectLocalSpace;
      return true;
   }

   return false;
}

