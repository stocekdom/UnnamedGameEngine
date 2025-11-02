#include <valarray>
#include "Arrow.h"
#include "../Base/Utility/Math.h"
#include "../Base/Scene.h"
//
// Created by dominik on 11.10.25.
//

Arrow::Arrow( const std::string& texturePath, sf::Vector2f position, float rotation,
              sf::Vector2f scale ) : Actor( texturePath, position, rotation, scale )
{
   centerPivot();
   createCollider();
}

void Arrow::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   scene.addTickableEntityToScene( shared_from_this() );
   collider->init( scene, collisionSystem );
   this->addChild( collider );
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
   this->move( delta );
   this->setRotation( std::atan2( velocity.y, velocity.x ) * Math::RADIAN_TO_DEG );
}

void Arrow::onCollision( const Collidable* other, CollisionInfo& info )
{
   hasHitTarget = true;
   velocity = { 0.f, 0.f };
   collider->setIsEnabled( false );
}

void Arrow::createCollider()
{
   collider = std::make_shared<ColliderPoint>( sf::Vector2f( ( sprite.getGlobalBounds().width * sprite.getScale().x ) / 2.0f, 0 ), this );
   collider->setIsEnabled( false );
}