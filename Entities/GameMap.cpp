#include <SFML/System/Vector2.hpp>
#include "GameMap.h"
#include "MapTile.h"

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
   for( size_t y = 0; y < mapHeight; ++y )
   {
      for( size_t x = 0; x < mapWidth; ++x )
      {
         float screenX = mapStart.x + ( float )x * ( SPRITE_WIDTH / 2 ) - ( float )y * ( SPRITE_WIDTH / 2 );
         float screenY = mapStart.y + ( float )y * ( SPRITE_HEIGHT / 2 ) + ( float )x * ( SPRITE_HEIGHT / 2 );
         auto tileTmp = std::make_shared<MapTile>( textureManager_, "Assets/grass1.png",
                                                   SPRITE_WIDTH, sf::Vector2f{ screenX, screenY } );
         tileTmp->init( scene, collisionSystem );
      }
   }
}
