//
// Created by dominik on 14.11.25.
//

#include "GameMap.h"
#include "../GameContext.h"
#include "MapTile.h"
#include "../../Src/Entities/ResourceFactory.h"
#include "../Core/Math.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <set>

GameMap::GameMap( int mapHeight, int mapWidth, const sf::Vector2f& mapStart, size_t seed )
   : mapWidth( mapWidth ), mapHeight( mapHeight ), mapStart( mapStart ), rng( seed )
{
}

void GameMap::generate( GameContext* context )
{
   auto enumMap = generator.generateMap( mapWidth, mapHeight, rng );
   regions = generator.generateRegions( enumMap, mapWidth, mapHeight, rng );

   for( int x = 0; x < mapWidth; ++x )
   {
      for( int y = 0; y < mapHeight; ++y )
      {
         float screenX = mapStart.x + static_cast<float>( x ) * ( Math::IsometricConstants::SPRITE_WIDTH / 2 ) -
                         static_cast<float>( y ) * ( Math::IsometricConstants::SPRITE_WIDTH / 2 );
         float screenY = mapStart.y + static_cast<float>( y ) * ( Math::IsometricConstants::SPRITE_HEIGHT / 2 ) +
                         static_cast<float>( x ) * ( Math::IsometricConstants::SPRITE_HEIGHT / 2 );

         // TODO move asset paths to another class
         auto tileTmp = context->scene->createFunctionalEntity<MapTile>(
            enumMap[ Math::coordsToIndex( x, y, mapWidth ) ].type == TileType::Water ? "Assets/water.png" : "Assets/grass.png",
            enumMap[ Math::coordsToIndex( x, y, mapWidth ) ], ActorParams{ sf::Vector2f{ screenX, screenY } } );

         gameMap.emplace_back( tileTmp );
      }
   }

   spawnResources( context );
}

/*
bool GameMap::onClick( const sf::Vector2f& location )
{
   auto tile = getTileIndex( location );
   if( tile.x < 0 || tile.y < 0 || tile.x >= mapWidth || tile.y >= mapHeight )
      return false;

   if( auto t = gameMap[ tile.x * mapWidth + tile.y ].lock() )

   return true;
}
*/
sf::Vector2f GameMap::snapToMapTile( const sf::Vector2f& mousePosition ) const
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

   return gameMap[ Math::coordsToIndex( tile.x, tile.y, mapWidth ) ];
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

TileIndex GameMap::generateStartingRegion()
{
   std::uniform_int_distribution<> dist( 0, static_cast<int>( regions.size() - 1 ) );
   auto& pickedRegion = regions[ dist( rng ) ];
   pickedRegion.isOwned = true;

   // Regions tiles are internal and their order doesn't matter so we can shuffle them internally
   std::ranges::shuffle( pickedRegion.tiles, rng );

   for( auto tile: pickedRegion.tiles )
      gameMap[ tile ]->onDiscovered();

   return Math::indexToCoords( pickedRegion.tiles[ 0 ], mapWidth );
}

sf::Vector2f GameMap::getScreenCoords( const TileIndex& tile ) const
{
   auto screenCoords = Math::worldToScreenSpace(
      sf::Vector2f{
         static_cast<float>( tile.x ) * Math::IsometricConstants::WORLD_TILE_WIDTH + Math::IsometricConstants::WORLD_TILE_WIDTH /
         2,
         static_cast<float>( tile.y ) * Math::IsometricConstants::WORLD_TILE_WIDTH + Math::IsometricConstants::WORLD_TILE_WIDTH /
         2
      } );

   screenCoords.x += Math::IsometricConstants::SPRITE_WIDTH / 2;
   screenCoords.x += mapStart.x;
   screenCoords.y += mapStart.y;
   return screenCoords;
}

void GameMap::discoverTiles( const TileIndex& tile, unsigned int radius ) const
{
   if( radius == 0 )
      return;

   if( tile.x < 0 || tile.y < 0 || tile.x >= mapWidth || tile.y >= mapHeight )
      return;

   using Node = std::pair<TileIndex, int>;

   std::set<unsigned int> visited;
   int offsets[ 4 ] = { -1, +1, -mapWidth, +mapWidth };
   std::queue<Node> tilesToProcess;

   tilesToProcess.emplace( tile, 0 );
   while( !tilesToProcess.empty() )
   {
      auto [ currentTile, distance ] = tilesToProcess.front();
      tilesToProcess.pop();

      const int index = Math::coordsToIndex( currentTile.x, currentTile.y, mapWidth );
      gameMap[ index ]->onDiscovered();

      if( distance >= radius )
         continue;

      for( auto offset: offsets )
      {
         int neighbor = index + offset;

         if( neighbor < 0 || neighbor >= gameMap.size() || visited.contains( neighbor ) )
            continue;

         visited.insert( neighbor );
         tilesToProcess.emplace( Math::indexToCoords( neighbor, mapWidth ), distance + 1 );
      }
   }
}

void GameMap::spawnResources( GameContext* context )
{
   for( auto& region: regions )
   {
      std::ranges::shuffle( region.tiles, rng );

      if( !region.tiles.empty() && Util::enumToIndex( Resources::ResourceSource::SOURCE_COUNT ) >= region.tiles.size() )
      {
         LOG_WARNING( "Couldn't generate enough resources for a region since it's too small" );
         break;
      }

      for( int i = 0; i < Util::enumToIndex( Resources::ResourceSource::SOURCE_COUNT ); ++i )
      {
         auto coords = Math::indexToCoords( region.tiles[ i ], mapWidth );

         float screenX = mapStart.x + static_cast<float>( coords.x ) * ( Math::IsometricConstants::SPRITE_WIDTH / 2 ) -
                         static_cast<float>( coords.y ) * ( Math::IsometricConstants::SPRITE_WIDTH / 2 );
         float screenY = mapStart.y + static_cast<float>( coords.y ) * ( Math::IsometricConstants::SPRITE_HEIGHT / 2 ) +
                         static_cast<float>( coords.x ) * ( Math::IsometricConstants::SPRITE_HEIGHT / 2 );
         auto& tile = gameMap[ region.tiles[ i ] ];
         // Offset the resource sources since they have a different origin set in ResourceActor
         tile->setResource( ResourceFactory::createResource( context->scene.get(), static_cast<Resources::ResourceSource>( i ), {
                                                                screenX + Math::IsometricConstants::SPRITE_WIDTH / 2,
                                                                screenY + 0.05f + Math::IsometricConstants::SPRITE_HEIGHT
                                                             } ) );
      }
   }
}
