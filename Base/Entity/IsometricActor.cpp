//
// Created by dominik on 14.11.25.
//
#include "IsometricActor.h"

IsometricActor::IsometricActor( TextureManager& textureManager, const std::string& texturePath, sf::Vector2f position,
                                float rotation, sf::Vector2f scale, float height, bool isVisible ) : Actor( textureManager,
                                                                                                            texturePath, position,
                                                                                                            rotation, scale,
                                                                                                            isVisible ),
                                                                                                     localHeight( height )
{
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
