//
// Created by dominik on 10.10.25.
//

#include "Target.h"
#include "../Base/Scene.h"

Target::Target( const std::string& texturePath, sf::Vector2f position, float rotation, sf::Vector2f scale ) : Actor(
      texturePath, position, rotation, scale ), rng( std::random_device{}() )
{
   centerPivot();
   createCollider();
}

void Target::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   scene.addEntityToScene( shared_from_this() );
   collider->init( scene, collisionSystem );
   this->addChild( collider );
}

// Default values optimized for 1920x1080 resolution.
void Target::randomize( float maxHeight, float minHeight, float maxWidth, float minWidth, float maxRotation, float minRotation,
                        float maxScale, float minScale )
{
   std::uniform_real_distribution<float> heightDist( minHeight, maxHeight );
   std::uniform_real_distribution<float> widthDist( minWidth, maxWidth );
   std::uniform_real_distribution<float> rotationDist( minRotation, maxRotation );
   std::uniform_real_distribution<float> scaleDist( minScale, maxScale );

   setPosition( sf::Vector2f( widthDist( rng ), heightDist( rng ) ) );
   setRotation( rotationDist( rng ) );
   float scale = scaleDist( rng );
   Target::setScale( sf::Vector2f( scale, scale ) );
}

void Target::createCollider()
{
   //sf::Vector2f colliderLocalTargetCenter( 72, 56 );
   collider = std::make_shared<ColliderRect>( sf::Vector2f( 2.0f, -6.0f ), sf::Vector2f( 10, 96 ), 0, this );
}

void Target::onCollision( const Collidable* other, CollisionInfo& info )
{
   // Calculate points based on hit position (distance from the target center).
   // Since a rectangle collider has a pivot at the center, the Y of CollisionInfo already tells us the distance from the center.
   ScoreboardUpdateEventData data( 0 );
   float localYAbs = std::abs( info.localPoint.y );

   if( localYAbs > 23 * sprite.getScale().y )
      data = ScoreboardUpdateEventData( 1 );
   else if( localYAbs > 5 * sprite.getScale().y )
      data = ScoreboardUpdateEventData( 2 );
   else
      data = ScoreboardUpdateEventData( 5 );

   notifyObservers( data );
}
