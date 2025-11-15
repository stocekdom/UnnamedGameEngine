#include "Scene.h"
//
// Created by dominik on 03.10.25.
//
const std::vector<std::shared_ptr<Entity>>& GameScene::getActors() const
{
   return actors;
}

void GameScene::addEntityToScene( const std::shared_ptr<Entity>& actor )
{
   actors.push_back( actor );
}

const std::vector<std::shared_ptr<Entity>>& GameScene::getTickableActors() const
{
   return tickableActors;
}

void GameScene::addTickableEntityToScene( const std::shared_ptr<Entity>& tickable )
{
   tickableActors.push_back( tickable );
}

void GameScene::updateFixed( float fixedDt )
{
   for( auto& actor: tickableActors )
   {
      actor->tickFixed( fixedDt );
   }
}

void GameScene::update( float deltaTime )
{
   for( auto& actor : actors )
   {
      actor->tick( deltaTime );
   }

   for( auto& actor: tickableActors )
   {
      actor->tick( deltaTime );
   }
}

const std::vector<std::shared_ptr<Observer>>& GameScene::getObservers() const
{
   return observers;
}

void GameScene::addObserver( const std::shared_ptr<Observer>& observer )
{
   observers.push_back( observer );
}

void GameScene::addGameMap( const std::shared_ptr<GameMap>& gameMap )
{
   map = gameMap;
}

void GameScene::handleLeftClick( const sf::Vector2f& position )
{
   map->onClick( position );
}

