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

GameMap::GameMap( int mapHeight, int mapWidth, const sf::Vector2f& mapStart, size_t seed )
   : mapWidth( mapWidth ), mapHeight( mapHeight ), mapStart( mapStart ), seed( seed ), generator( seed )
{
}

void GameMap::generate( GameContext* context )
{
   auto enumMap = generator.generateMap( mapWidth, mapHeight );
   generator.generateRegions( enumMap, mapWidth, mapHeight );

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

         if( ( x + y * mapWidth ) % 9 == 0 && enumMap[ Math::coordsToIndex( x, y, mapWidth ) ].type == TileType::Land )
         {
            // Here we add 0.05f since the resource has the same coords as the tile and we don't want clipping due to float errors
            auto res = ResourceFactory::createResource( context->scene.get(), Resources::ResourceSource::STONES,
                                                        { screenX, screenY + 0.05f } );
            tileTmp->setResource( res );
         }
         /*
         // Temporary for testing. Done like this so the weakptr from shared_ptr to resource doesnt expire immediately
         if( ( x + y * mapWidth ) % 9 == 0 )
         {
            auto res = ResourceFactory::createResource( Resources::ResourceSource::STONES, {
                                                           Math::IsometricConstants::SPRITE_HEIGHT,
                                                           Math::IsometricConstants::SPRITE_HEIGHT
                                                        } );
            tileTmp->setResource( res );
            tileTmp->onStart( context );
         }
         else if( ( x + y * mapWidth ) % 12 == 0 )
         {
            auto res = ResourceFactory::createResource( Resources::ResourceSource::TREE, {
                                                           Math::IsometricConstants::SPRITE_HEIGHT,
                                                           Math::IsometricConstants::SPRITE_HEIGHT
                                                        } );
            tileTmp->setResource( res );
            tileTmp->onStart( context );
         }
         else
         {
            tileTmp->onStart( context );
         }
         */
         gameMap.emplace_back( tileTmp );
      }
   }
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

sf::Vector2f GameMap::getScreenCoords( const sf::Vector2i& tile ) const
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
