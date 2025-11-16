#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "../Base/Scene.h"
#include "GameMap.h"
#include "MapTile.h"
#include "../Base/Core/Math.h"

//
// Created by dominik on 14.11.25.
//
GameMap::GameMap( TextureManager& textureManager, size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart ) : mapHeight(
      mapHeight ),
                                                                                                                      mapStart(
                                                                                                                            mapStart ),
                                                                                                                      mapWidth(
                                                                                                                            mapWidth ),
                                                                                                                      textureManager_(
                                                                                                                            textureManager )
{
}

void GameMap::init( GameScene& scene, CollisionSystem& collisionSystem )
{
   scene.addGameMap( shared_from_this() );

   for( size_t x = 0; x < mapWidth; ++x )
   {
      for( size_t y = 0; y < mapHeight; ++y )
      {
         float screenX = mapStart.x + ( float )x * ( SPRITE_WIDTH / 2 ) - ( float )y * ( SPRITE_WIDTH / 2 );
         float screenY = mapStart.y + ( float )y * ( SPRITE_HEIGHT / 2 ) + ( float )x * ( SPRITE_HEIGHT / 2 );
         auto tileTmp = std::make_shared<MapTile>( textureManager_, "Assets/grass1.png", Mobility::STATIC, SPRITE_WIDTH,
                                                   sf::Vector2f{ screenX, screenY } );
         tileTmp->onStart( scene, collisionSystem );
         gameMap.push_back( tileTmp );
      }
   }
}

void GameMap::onClick( const sf::Vector2f& location )
{
   // Offset the click location to the center of the map in screen space. The center of the map is considered the top corner of the diamond
   auto mapStartOffsetLocation = location - mapStart;
   // Offset again by half the sprite width to get the center of the tile
   mapStartOffsetLocation.x -= SPRITE_WIDTH / 2;
   auto worldLocation = Math::IsoSpace::screenToWorldSpace( mapStartOffsetLocation );
   int worldX = std::floor( worldLocation.x / WORLD_TILE_WIDTH );
   int worldY = std::floor( worldLocation.y / WORLD_TILE_WIDTH );

   if( worldX < 0 || worldY < 0 || worldX >= mapWidth || worldY >= mapHeight )
      return;

   if( auto t = gameMap[ worldX * mapWidth + worldY ].lock() )
      t->setHeight( 10 );
}
