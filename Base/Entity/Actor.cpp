//
// Created by dominik on 03.10.25.
//
#include <string>
#include <stdexcept>
#include "Actor.h"

// TODO DRY broken in constructor. Make a method for setting and loading sprite
Actor::Actor( const std::string& texturePath, sf::Vector2f position, float rotation, sf::Vector2f scale ) : isVisibleActor( true ),
                                                                                                            rotation( rotation )
{
   if( !texture.loadFromFile( texturePath ) )
   {
      throw std::runtime_error( "Could not load texture at " + texturePath );
   }

   sprite.setTexture( texture );
   sprite.setPosition( position );
   sprite.setRotation( rotation );
   sprite.setScale( scale );
}

void Actor::centerPivot()
{
   sprite.setOrigin( sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 );
}

sf::Vector2f Actor::getPosition() const
{
   return sprite.getPosition();
}

float Actor::getRotation() const
{
   return rotation;
}

sf::Vector2f Actor::getScale() const
{
   return sprite.getScale();
}

bool Actor::isVisible() const
{
   return isVisibleActor;
}

void Actor::setScale( const sf::Vector2f& scale )
{
   sprite.setScale( scale );
}

void Actor::setTexture( const sf::Texture& inTexture )
{
   sprite.setTexture( inTexture );
}

void Actor::setSprite( const sf::Sprite& inSprite )
{
   sprite = inSprite;
}

void Actor::setPosition( const sf::Vector2f& inPosition )
{
   sprite.setPosition( inPosition );
}

void Actor::setRotation( float inRotation )
{
   rotation = inRotation;
   sprite.setRotation( inRotation );
}

void Actor::setIsVisibleEntity( bool isVisibleEntity )
{
   isVisibleActor = isVisibleEntity;
}

void Actor::tickFixed( float fixedDt )
{
}

void Actor::tick( float deltaTime )
{
}

void Actor::onCollision( const Actor* other, CollisionInfo& info )
{
}

const sf::Drawable& Actor::getDrawable()
{
   return sprite;
}





