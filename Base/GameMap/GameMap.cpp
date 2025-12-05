#include "../Scene.h"
#include "GameMap.h"
#include "MapTile.h"
#include "../Core/Math.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

//
// Created by dominik on 14.11.25.
//
GameMap::GameMap( size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart )
      : mapHeight( mapHeight ), mapStart( mapStart ), mapWidth( mapWidth )
{
}

void GameMap::init( GameContext* context )
{
   for( size_t x = 0; x < mapWidth; ++x )
   {
      for( size_t y = 0; y < mapHeight; ++y )
      {
         float screenX = mapStart.x + ( float )x * ( Math::IsometricConstants::SPRITE_WIDTH / 2 ) -
                         ( float )y * ( Math::IsometricConstants::SPRITE_WIDTH / 2 );
         float screenY = mapStart.y + ( float )y * ( Math::IsometricConstants::SPRITE_HEIGHT / 2 ) +
                         ( float )x * ( Math::IsometricConstants::SPRITE_HEIGHT / 2 );
         auto tileTmp = std::make_shared<MapTile>( "Assets/grass1.png", SpawnCategory::WORLD, Mobility::STATIC,
                                                   sf::Vector2f{ screenX, screenY } );
         tileTmp->onStart( context );
         gameMap.push_back( tileTmp );
      }
   }
}

bool GameMap::onClick( const sf::Vector2f& location )
{
   auto tile = getTileIndex( location );
   if( tile.x < 0 || tile.y < 0 || tile.x >= mapWidth || tile.y >= mapHeight )
      return false;

   if( auto t = gameMap[ tile.x * mapWidth + tile.y ].lock() )
      t->setHeight( 10 );

   return true;
}

sf::Vector2f GameMap::snapToMapTile( const sf::Vector2f& mousePosition )
{
   auto tile = getTileIndex( mousePosition );

   if( tile.x < 0 || tile.y < 0 || tile.x >= mapWidth || tile.y >= mapHeight )
      return mousePosition;

   return getScreenCoords( tile );
}

std::weak_ptr<MapTile> GameMap::getMapTile( const sf::Vector2f& mousePosition )
{
   auto tile = getTileIndex( mousePosition );
   if( tile.x < 0 || tile.y < 0 || tile.x >= mapWidth || tile.y >= mapHeight )
      return {};

   return gameMap[ tile.x * mapWidth + tile.y ];
}

sf::Vector2i GameMap::getTileIndex( const sf::Vector2f& position ) const
{
   // Offset the click location to the center of the map in screen space. The center of the map is considered the top corner of the diamond
   auto mapStartOffsetLocation = position - mapStart;
   // Offset again by half the sprite width to get the center of the tile
   mapStartOffsetLocation.x -= Math::IsometricConstants::SPRITE_WIDTH / 2;
   auto worldLocation = Math::screenToWorldSpace( mapStartOffsetLocation );
   int worldX = std::floor( worldLocation.x / Math::IsometricConstants::WORLD_TILE_WIDTH );
   int worldY = std::floor( worldLocation.y / Math::IsometricConstants::WORLD_TILE_WIDTH );
   return { worldX, worldY };
}

sf::Vector2f GameMap::getScreenCoords( const sf::Vector2i& tile ) const
{
   auto screenCoords = Math::worldToScreenSpace(
         sf::Vector2f{
               ( float )tile.x * Math::IsometricConstants::WORLD_TILE_WIDTH + Math::IsometricConstants::WORLD_TILE_WIDTH / 2,
               ( float )tile.y * Math::IsometricConstants::WORLD_TILE_WIDTH + Math::IsometricConstants::WORLD_TILE_WIDTH / 2 } );

   screenCoords.x += Math::IsometricConstants::SPRITE_WIDTH / 2;
   screenCoords.x += mapStart.x;
   screenCoords.y += mapStart.y;
   return screenCoords;
}
