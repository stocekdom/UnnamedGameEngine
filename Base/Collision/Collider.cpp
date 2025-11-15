//
// Created by dominik on 13.10.25.
//
#include "Collider.h"
#include "CollisionSystem.h"
#include "../Scene.h"

Collider::Collider( Collidable* owningActor, sf::Vector2f position, float rotation, sf::Vector2f scale, bool isVisible ) : SpacialEntity( position,
                                                                                                                                          rotation,
                                                                                                                                          scale,
                                                                                                                                          isVisible ),
                                                                                                                           owner( owningActor ),
                                                                                                                           isEnabled( true )
{
}

const Collidable* Collider::getOwner() const
{
   return owner;
}

void Collider::onCollision( const Collidable* other, CollisionInfo& info )
{
   if( owner != nullptr )
   {
      owner->onCollision( other, info );
   }
}

bool Collider::isColliderEnabled() const
{
   return isEnabled;
}

void Collider::setIsEnabled( bool enabled )
{
   isEnabled = enabled;
}

void Collider::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   auto entity = shared_from_this();
   scene.addEntityToScene( entity );

   std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>( entity );
   if( collider )
   {
      collisionSystem.registerCollider( collider );
   }
}
