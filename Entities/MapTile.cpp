#include "MapTile.h"
#include "../Base/TextureManager.h"
#include "../Base/Entity/Actor.h"

//
// Created by dominik on 14.11.25.
//
MapTile::MapTile( TextureManager& textureManager, const std::string& texturePath, float tileWidth,
                  const sf::Vector2<float>& position, float rotation, const sf::Vector2<float>& scale, float height, bool isVisible )
      : IsometricActor( textureManager, texturePath, position, rotation, scale, height, isVisible )
{
   // Calculate scale based on tile width so all tiles have the same size.
   // We use width because all isometric tiles can be blocks and height tells us nothing about the tile.
   // We need to know the size of the base which is and the height is width/2.
   // See Assets/grass.png for an example. We need to know the dimensions of the isometric diamond.
   float scaleX = tileWidth / sprite.getLocalBounds().width;
   localScale = { scaleX, scaleX };
}

void MapTile::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   Actor::init( scene, collisionSystem );
   //sprite.setOrigin( sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2 );
}
