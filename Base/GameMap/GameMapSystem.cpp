//
// Created by dominik on 04.12.25.
//
#include "GameMapSystem.h"
#include "GameMap.h"
#include <iostream>

void GameMapSystem::onStart( GameContext* context )
{
   if( map )
      map->init( context );
   else
      std::cout << "\033[93m[WARN]: Map it not initialized]" << "\033[0m" << std::endl;

   scene = context->scene.get();
}

void GameMapSystem::generateMap( size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart, size_t seed )
{
   // TODO make procedural map generation
   map = std::make_unique<GameMap>( mapHeight, mapWidth, mapStart );
}

sf::Vector2f GameMapSystem::snapToMapTile( const sf::Vector2i& mousePosition ) const
{
   return map->snapToMapTile( scene->getWorldCoordinates( mousePosition ) );
}

std::weak_ptr<MapTile> GameMapSystem::getMapTile( const sf::Vector2i& mousePosition ) const
{
   return map->getMapTile( scene->getWorldCoordinates( mousePosition ) );
}

bool GameMapSystem::placeBuilding( const sf::Vector2i& position, const std::shared_ptr<Building>& building ) const
{
   auto tile = map->getMapTile( scene->getWorldCoordinates( position ) ).lock();

   if( !tile )
      return false;

   if( !tile->isOccupied() )
   {
      tile->setBuilding( building );
      return true;
   }

   return false;
}
