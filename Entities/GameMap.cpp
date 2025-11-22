#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "../Base/Scene.h"
#include "GameMap.h"
#include "MapTile.h"
#include "../Base/Core/Math.h"

//
// Created by dominik on 14.11.25.
//
GameMap::GameMap( size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart )
      : mapHeight( mapHeight ), mapStart( mapStart ), mapWidth( mapWidth )
{
}

void GameMap::init( std::shared_ptr<GameContext>& context )
{
   context->scene->addGameMap( shared_from_this() );

   for( size_t x = 0; x < mapWidth; ++x )
   {
      for( size_t y = 0; y < mapHeight; ++y )
      {
         float screenX = mapStart.x + ( float )x * ( Math::IsometricConstants::SPRITE_WIDTH / 2 ) -
                         ( float )y * ( Math::IsometricConstants::SPRITE_WIDTH / 2 );
         float screenY = mapStart.y + ( float )y * ( Math::IsometricConstants::SPRITE_HEIGHT / 2 ) +
                         ( float )x * ( Math::IsometricConstants::SPRITE_HEIGHT / 2 );
         auto tileTmp = std::make_shared<MapTile>( "Assets/grass1.png", Mobility::STATIC, sf::Vector2f{ screenX, screenY } );
         tileTmp->onStart( context );
         gameMap.push_back( tileTmp );
      }
   }
}

bool GameMap::onClick( const sf::Vector2f& location )
{
   // Offset the click location to the center of the map in screen space. The center of the map is considered the top corner of the diamond
   auto mapStartOffsetLocation = location - mapStart;
   // Offset again by half the sprite width to get the center of the tile
   mapStartOffsetLocation.x -= Math::IsometricConstants::SPRITE_WIDTH / 2;
   auto worldLocation = Math::IsoSpace::screenToWorldSpace( mapStartOffsetLocation );
   int worldX = std::floor( worldLocation.x / Math::IsometricConstants::WORLD_TILE_WIDTH );
   int worldY = std::floor( worldLocation.y / Math::IsometricConstants::WORLD_TILE_WIDTH );

   if( worldX < 0 || worldY < 0 || worldX >= mapWidth || worldY >= mapHeight )
      return false;

   if( auto t = gameMap[ worldX * mapWidth + worldY ].lock() )
      t->setHeight( 10 );

   return true;
}
