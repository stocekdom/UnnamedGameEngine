//
// Created by dominik on 03.10.25.
//
#include <string>
#include <stdexcept>
#include <valarray>
#include "Actor.h"
#include "../Scene.h"

Actor::Actor( TextureManager& textureManager, const std::string& texturePath, sf::Vector2f position, float rotation, sf::Vector2f scale,
              bool isVisible ) : SpacialEntity( position, rotation, scale, isVisible )
{
   sprite.setTexture( textureManager.loadTexture( texturePath ) );
   isEntityDirty = true;
}

void Actor::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   scene.addEntityToScene( shared_from_this() );
}

void Actor::centerPivot()
{
   sprite.setOrigin( sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 );
}

sf::Vector2f Actor::getParentRelativePosition() const
{
   return localPosition;
}

const sf::Drawable& Actor::getDrawable()
{
   return sprite;
}

void Actor::setTexture( const sf::Texture& inTexture )
{
   sprite.setTexture( inTexture );
}

void Actor::setSprite( const sf::Sprite& inSprite )
{
   sprite = inSprite;
}

void Actor::tick( float deltaTime )
{
   if( isEntityDirty )
   {
      sprite.setPosition( getPosition() );
      sprite.setScale( getScale() );
      sprite.setRotation( getRotation() );
      isEntityDirty = false;
   }
}
