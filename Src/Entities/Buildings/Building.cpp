//
// Created by dominik on 03.12.25.
//

#include "Building.h"
#include "../../../Base/GameMap/MapTile.h"

Building::Building( SpawnCategory spawnCategory, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale,
                    float height, bool isVisible )
   : IsometricActor( spawnCategory, Mobility::STATIC, position, rotation, scale, height, isVisible )
{
}

void Building::onStart( GameContext* context )
{
   // Ensures all buildings have the same pivot point.
   sprite.setOrigin( sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height );
   IsometricActor::onStart( context );
}

void Building::setOverlayColor( const sf::Color& color )
{
   sprite.setColor( color );
}

bool Building::canBePlaced( const std::shared_ptr<MapTile>& tile )
{
   return !tile->isOccupied();
}

void Building::onPlaced( const std::shared_ptr<MapTile>& tile )
{
}
