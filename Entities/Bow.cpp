//
// Created by dominik on 09.10.25.
//
#include <cmath>
#include "../Base/Utility/Math.h"
#include "Bow.h"
#include "../Base/Scene.h"

Bow::Bow( const std::string& texturePath, sf::Vector2f position, float rotation, sf::Vector2f scale ) : Actor( texturePath, position, rotation,
                                                                                                               scale )
{
   centerPivot();
}

void Bow::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   auto arrowTmp = std::make_shared<Arrow>( "Assets/arrow.png" );
   arrowTmp->init( scene, collisionSystem );
   scene.addEntityToScene( shared_from_this() );
   this->addChild( arrowTmp );
   arrow = arrowTmp;
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
      // Detach the arrow so it doesn't move in local space, since it's scaled down. We will only reset the position after firing the arrow
      if( !a->isArrowFired() )
      {
         // Place into world space after firing (detaching)
         a->setParent( nullptr );
         // TODO we only have one child, but this is fragile. Need entity ids and map to do this properly
         // TODO cleaner option is to implement abstract class with sockets instead of linking the entities as children
         this->children.clear();
         a->setScale( this->getScale() );
         a->setRotation( this->getRotation() );
      }

      // Recall the arrow
      a->setPosition( this->getPosition() );
      // Calculate the initial velocity of the arrow
      // vx = cos(theta) * chargeLevel
      // vy = sin(theta) * chargeLevel
      // https://en.wikipedia.org/wiki/Projectile_motion
      a->fire( sf::Vector2f( std::cos( ( this->getRotation() * Math::DEG_TO_RADIAN ) ) * chargeLevel,
                             std::sin( ( this->getRotation() * Math::DEG_TO_RADIAN ) ) * chargeLevel ) );
      chargeLevel = 0;
   }
}

void Bow::tick( float deltaTime )
{
   if( rotationSpeed != 0 )
   {
      localRotation = std::clamp( localRotation + ( rotationSpeed * deltaTime ), -MAX_ANGLE, MAX_ANGLE );
      setDirty();
   }

   Actor::tick( deltaTime );
   chargeLevel = std::min( chargeLevel + ( chargeSpeed * deltaTime ), MAX_CHARGE );
}

void Bow::setRotationSpeed( float rotation )
{
   rotationSpeed = rotation;
}
