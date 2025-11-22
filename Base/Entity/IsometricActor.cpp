//
// Created by dominik on 14.11.25.
//
#include "IsometricActor.h"

IsometricActor::IsometricActor( Mobility mobilityStatus, sf::Vector2f position, float rotation, sf::Vector2f scale, float height,
                                bool isVisible )
      : Actor( mobilityStatus, position, rotation, scale, isVisible ), localHeight( height )
{
}

void IsometricActor::onStart( std::shared_ptr<GameContext>& context )
{
   // TODO Temporary texture for testing. remove
   sprite.setTexture( context->textureManager->loadTexture( "Assets/gov_center.png" ) );
   sprite.setOrigin( sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height );
   Actor::onStart( context );
}

float IsometricActor::getHeight() const
{
   return localHeight;
}

void IsometricActor::setHeight( float newHeight )
{
   localHeight = newHeight;
   setDirty();
}

void IsometricActor::tick( float deltaTime )
{
   if( isEntityDirty )
   {
      auto pos = getPosition();
      sprite.setPosition( { pos.x, pos.y - localHeight } );
      sprite.setScale( getScale() );
      sprite.setRotation( getRotation() );
      isEntityDirty = false;
   }
}

sf::Vector2f IsometricActor::getPosition() const
{
   auto pos = SpacialEntity::getPosition();
   return { pos.x, pos.y - localHeight };
}
