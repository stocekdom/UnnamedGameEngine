//
// Created by dominik on 09.10.25.
//
#include <cmath>
#include "Bow.h"

Bow::Bow( const std::string& texturePath, sf::Vector2f position, float rotation, sf::Vector2f scale ) : Actor( texturePath, position, rotation, scale )
{
}

void Bow::charge( float speed )
{
   chargeSpeed = speed;
}

void Bow::fire()
{
   chargeSpeed = 0;

   if( auto a = arrow.lock() )
   {
      // Recall the arrow
      a->setPosition( sprite.getPosition() );
      // Calculate the initial velocity of the arrow
      // vx = cos(theta) * chargeLevel
      // vy = sin(theta) * chargeLevel
      // https://en.wikipedia.org/wiki/Projectile_motion
      a->fire( sf::Vector2f( std::cos( ( rotation * DEG_TO_RADIAN ) ) * chargeLevel, std::sin( ( rotation * DEG_TO_RADIAN ) ) * chargeLevel ) );
      chargeLevel = 0;
   }
}

void Bow::rotate( float speed )
{
   rotationSpeed = speed;
}

void Bow::tick( float deltaTime )
{
   rotation = std::clamp( rotation + ( rotationSpeed * deltaTime ), -MAX_ANGLE, MAX_ANGLE );
   sprite.setRotation( rotation );
   if( auto a = arrow.lock() )
      if( !a->isArrowFired() )
         a->setRotation( rotation );
   chargeLevel = std::min( chargeLevel + ( chargeSpeed * deltaTime ), MAX_CHARGE );
}

void Bow::tickFixed( float fixedDt )
{
   Actor::tickFixed( fixedDt );
}

void Bow::setArrow( const std::shared_ptr<Arrow>& newArrow )
{
   arrow = newArrow;

   if( auto a = arrow.lock() )
   {
      a->setPosition( sprite.getPosition() );
   }
}







