//
// Created by dominik on 01.11.25.
//

#ifndef GAME1_COLLISIONHELPER_H
#define GAME1_COLLISIONHELPER_H

#include <valarray>
#include "ColliderPoint.h"
#include "ColliderRect.h"

class Collisions
{
   public:
      static bool pointRectangleCollisionHelper( const ColliderPoint* point, const ColliderRect* rect, CollisionInfo& info )
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

      static bool pointPointCollisionHelper( const ColliderPoint* point, const ColliderPoint* otherPoint, CollisionInfo& info )
      {
         auto worldPos = point->getPosition();

         if( worldPos != otherPoint->getPosition() )
            return false;

         info.localPoint = { 0, 0 };
         info.worldPoint = worldPos;
         return true;
      }
};

#endif //GAME1_COLLISIONHELPER_H
