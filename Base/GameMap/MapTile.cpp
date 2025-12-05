//
// Created by dominik on 14.11.25.
//
#include "MapTile.h"
#include "../Core/Math.h"
#include <utility>

MapTile::MapTile( std::string texturePath, SpawnCategory spawnCategory, Mobility mobilityStatus,
                  const sf::Vector2<float>& position, float rotation, const sf::Vector2<float>& scale, float height,
                  bool isVisible )
      : IsometricActor( spawnCategory, mobilityStatus, position, rotation, scale, height, isVisible ),
        tileTexture( std::move( texturePath ) )
{
}

void MapTile::onStart( GameContext* context )
{
   sprite.setTexture( context->textureManager->loadTexture( tileTexture ) );
   // Calculate scale based on tile width so all tiles have the same size.
   // We use width because all isometric tiles can be blocks and height tells us nothing about the tile.
   // We need to know the size of the base which is and the height is width/2.
   // See Assets/grass.png for an example. We need to know the dimensions of the isometric diamond.
   float scaleX = Math::IsometricConstants::SPRITE_WIDTH / sprite.getLocalBounds().width;
   localScale = { scaleX, scaleX };
   Actor::onStart( context );
   // Force the origin to be in the top-left corner.
   sprite.setOrigin( 0, 0 );
}

bool MapTile::isOccupied() const
{
   return building.lock() != nullptr;
}

void MapTile::setBuilding( const std::shared_ptr<Building>& newBuilding )
{
   building = newBuilding;
}
