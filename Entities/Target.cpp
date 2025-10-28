//
// Created by dominik on 10.10.25.
//
#include <iostream>
#include "Target.h"

Target::Target( const std::string& texturePath, CollisionSystem& system, sf::Vector2f position, float rotation, sf::Vector2f scale ) : Actor(
      texturePath, position, rotation, scale ), rng( std::random_device{}() )
{
   createCollider( system );
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

void Target::createCollider( CollisionSystem& system )
{
   centerPivot();
   // Calculate world space coordinates of the collider center from the target's local space coordinates, since we have no GUI.
   sf::Vector2f colliderLocalTargetCenter( 72, 56 );
   sf::Vector2f colliderWorldTargetCenter = sprite.getTransform().transformPoint( colliderLocalTargetCenter );
   collider = std::make_shared<ColliderRect>( colliderWorldTargetCenter, sf::Vector2f( 20, 96 ), rotation, this );
   system.registerCollider( collider );
}

void Target::setPosition( const sf::Vector2f& newPosition )
{
   sf::Vector2f delta = newPosition - sprite.getPosition();
   Actor::setPosition( newPosition );
   collider->move( delta );
}

void Target::setRotation( float newRotation )
{
   Actor::setRotation( rotation );
   collider->setRotation( rotation );
}

void Target::setScale( const sf::Vector2f& newScale )
{
   Actor::setScale( newScale );
   collider->setScale( newScale );
}

void Target::onCollision( const Actor* other, CollisionInfo& info )
{
   std::cout << "Collision local space " << info.localPoint.x << ", " << info.localPoint.y << " Scale:" << sprite.getScale().x << std::endl;
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
