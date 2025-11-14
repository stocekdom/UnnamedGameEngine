#include "MapTile.h"
#include "../Base/TextureManager.h"
#include "../Base/Entity/Actor.h"

//
// Created by dominik on 14.11.25.
//
MapTile::MapTile( TextureManager& textureManager, const std::__cxx11::basic_string<char>& texturePath,
                  const sf::Vector2<float>& position, float rotation, const sf::Vector2<float>& scale, bool isVisible ) : Actor(
      textureManager, texturePath, position, rotation, scale, isVisible )
{
}

void MapTile::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   Actor::init( scene, collisionSystem );
   //sprite.setOrigin( sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 );
}
