//
// Created by dominik on 13.10.25.
//
#include "ICollider.h"
#include "CollisionSystem.h"
#include "../Scene.h"

ICollider::ICollider( Collidable* owningActor, sf::Vector2f position, float rotation, sf::Vector2f scale, bool isVisible ) : SpacialEntity( position,
                                                                                                                                            rotation,
                                                                                                                                            scale,
                                                                                                                                            isVisible ),
                                                                                                                             owner( owningActor ),
                                                                                                                             isEnabled( true )
{
}

const Collidable* ICollider::getOwner() const
{
   return owner;
}

void ICollider::onCollision( const Collidable* other, CollisionInfo& info )
{
   if( owner != nullptr )
   {
      owner->onCollision( other, info );
   }
}

bool ICollider::isColliderEnabled() const
{
   return isEnabled;
}

void ICollider::setIsEnabled( bool enabled )
{
   isEnabled = enabled;
}

void ICollider::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   auto entity = shared_from_this();
   scene.addEntityToScene( entity );

   std::shared_ptr<ICollider> collider = std::dynamic_pointer_cast<ICollider>( entity );
   if( collider )
   {
      collisionSystem.registerCollider( collider );
   }
}
