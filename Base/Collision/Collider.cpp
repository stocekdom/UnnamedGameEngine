//
// Created by dominik on 13.10.25.
//
#include "Collider.h"
#include "CollisionSystem.h"

Collider::Collider( Collidable* owningActor, Mobility mobilityStatus, sf::Vector2f position, float rotation,
                    sf::Vector2f scale, bool isVisible )
      : SpacialEntity( mobilityStatus, position, rotation, scale, isVisible ), owner( owningActor ), isEnabled( true )
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

void Collider::onStart( std::shared_ptr<GameContext>& context )
{
   auto entity = shared_from_this();
   context->scene->addEntityToScene( entity );

   std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>( entity );
   if( collider )
   {
      context->collisionSystem->registerCollider( collider );
   }
}
