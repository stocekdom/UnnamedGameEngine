//
// Created by dominik on 13.10.25.
//
#include "CollisionSystem.h"
#include "Collider.h"

void CollisionSystem::registerCollider( const std::shared_ptr<Collider>& collider )
{
   collider->setIsVisibleEntity( isDebugged );
   colliders.push_back( collider );
}

const std::vector<std::weak_ptr<Collider>>& CollisionSystem::getColliders() const
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

void CollisionSystem::debugSwitch()
{
   for( auto& collider: colliders )
   {
      if( auto c = collider.lock() )
         c->setIsVisibleEntity( !isDebugged );

      isDebugged = !isDebugged;
   }
}
