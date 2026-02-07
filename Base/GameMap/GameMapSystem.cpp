//
// Created by dominik on 04.12.25.
//
#include "GameMapSystem.h"
#include "GameMap.h"
#include "../../Src/Entities/Buildings/Building.h"
#include "../Logging/Logger.h"

void GameMapSystem::init( GameContext* context )
{
   context_ = context;
}

void GameMapSystem::onStart()
{
   if( !map )
      LOG_WARNING( "Map it not generated and cannot be initialized!" );
}

void GameMapSystem::update( float dt )
{
}

void GameMapSystem::generateMap( size_t mapHeight, size_t mapWidth, const sf::Vector2f& mapStart, size_t seed )
{
   // TODO make procedural map generation
   map = std::make_unique<GameMap>( mapHeight, mapWidth, mapStart, seed );
   map->generate( context_ );
}

SnapToTileResult GameMapSystem::snapToMapTile( const sf::Vector2i& mousePosition ) const
{
   auto pos = map->snapToMapTile( context_->scene->getWorldCoordinates( mousePosition ) );
   auto tile = map->getMapTile( pos );

   return { pos, tile };
}

std::weak_ptr<MapTile> GameMapSystem::getMapTile( const sf::Vector2i& mousePosition ) const
{
   return map->getMapTile( context_->scene->getWorldCoordinates( mousePosition ) );
}

bool GameMapSystem::placeBuilding( const sf::Vector2i& position, const std::shared_ptr<Building>& building ) const
{
   auto tile = map->getMapTile( context_->scene->getWorldCoordinates( position ) ).lock();

   if( !tile )
      return false;

   if( building->canBePlaced( tile ) )
   {
      tile->setBuilding( building );
      building->onPlaced( tile );
      return true;
   }

   return false;
}
