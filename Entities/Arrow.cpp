//
// Created by dominik on 11.10.25.
//
#include <valarray>
#include "Arrow.h"
#include "../Base/Utility/Math.h"
#include "../Base/ColliderPoint.h"

Arrow::Arrow( const std::string& texturePath, CollisionSystem& system, sf::Vector2f position, float rotation, sf::Vector2f scale ) : Actor(
      texturePath, position, rotation, scale )
{
   createCollider( system );
}

void Arrow::fire( sf::Vector2f initialVelocity )
{
   isFired = true;
   hasHitTarget = false;
   velocity = initialVelocity;
   collider->setIsEnabled( true );
}

bool Arrow::isArrowFired() const
{
   return isFired;
}

bool Arrow::hasArrowHitTarget() const
{
   return hasHitTarget;
}

void Arrow::tickFixed( float fixedDt )
{
   if( !isFired || hasHitTarget )
      return;

   // Each time interval (tick) move the arrow by the distance it has moved in the last interval.
   // Vy = V0 * sin(theta) - ( g * t )
   // Because d = Vy * t, Y(t) = V0 * sin(theta) * t - ( g * t^2 ) / 2
   // Instead of calculating this as a function of time,
   // each tick we update the velocity with -g * t and the position by the amount of distance the projectile traveled in gt.
   // https://en.wikipedia.org/wiki/Projectile_motion
   velocity.y += Math::GRAVITY * fixedDt;
   sf::Vector2f delta = velocity * fixedDt * Math::PIXELS_PER_METER;
   setPosition( sprite.getPosition() + delta );
   setRotation( std::atan2( velocity.y, velocity.x ) * Math::PIXELS_PER_METER );
}

void Arrow::onCollision( const Actor* other, CollisionInfo& info )
{
   hasHitTarget = true;
   velocity = { 0.f, 0.f };
   collider->setIsEnabled( false );
}

void Arrow::setRotation( float inRotation )
{
   // No collider nullptr checking, because the arrow must have a collider.
   // Otherwise, it's a critical failure and the program should end.

   rotation = inRotation;
   // Transform the point to the local space of the actor.
   sf::Vector2f localPoint = sprite.getInverseTransform().transformPoint( collider->getPosition() );
   // Update the actor's rotation.
   sprite.setRotation( inRotation );
   // Transform the point back to global space with the new rotation.
   sf::Vector2f worldSpacePoint = sprite.getTransform().transformPoint( localPoint );
   collider->setPosition( worldSpacePoint );
}

void Arrow::createCollider( CollisionSystem& system )
{
   // TODO Counting collider like this sucks. Use local space coordinates instead. Tree structure?.
   centerPivot();
   collider = std::make_shared<ColliderPoint>(
         sf::Vector2f( ( sprite.getPosition().x + ( sprite.getGlobalBounds().width * sprite.getScale().x ) / 2.f ), sprite.getPosition().y ), this );
   collider->setIsEnabled( false );
   system.registerCollider( collider );
}

void Arrow::setPosition( const sf::Vector2f& position )
{
   // Calculate the rotated tip offset:
   sf::Vector2f localPoint = sprite.getInverseTransform().transformPoint( collider->getPosition() );
   sprite.setPosition( position );
   sf::Vector2f worldSpacePoint = sprite.getTransform().transformPoint( localPoint );
   collider->setPosition( worldSpacePoint );
}

void Arrow::setScale( const sf::Vector2f& scale )
{
   sf::Vector2f localPoint = sprite.getInverseTransform().transformPoint( collider->getPosition() );
   Actor::setScale( scale );
   sf::Vector2f worldSpacePoint = sprite.getTransform().transformPoint( localPoint );
   collider->setPosition( worldSpacePoint );
}

