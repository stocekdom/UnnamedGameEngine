//
// Created by dominik on 13.10.25.
//
#include "Collider.h"
#include "CollisionSystem.h"

Collider::Collider( Collidable* owningActor, Mobility mobilityStatus, sf::Vector2f position, float rotation,
                    sf::Vector2f scale, bool isVisible )
   : SpacialEntity( mobilityStatus, position, rotation, scale, isVisible ), isEnabled( true ), owner( owningActor )
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

void Collider::onStart( GameContext* context )
{
   const auto entity = shared_from_this();
   context->scene->addEntityToScene( entity );

   if( const std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>( entity ) )
   {
      context->collisionSystem->registerCollider( collider );
   }
}
