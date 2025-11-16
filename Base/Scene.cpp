#include "Scene.h"

//
// Created by dominik on 03.10.25.
//
void GameScene::addEntityToScene( const std::shared_ptr<Entity>& actor )
{
   switch( actor->getMobility() )
   {
      case Mobility::STATIC:
         staticActors.push_back( actor );
         break;
      case Mobility::MOVABLE:
         movableActors.push_back( actor );
         break;
      default:
         // TODO add logging
         throw std::runtime_error( "Unknown mobility type" );
   }
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
   for( auto& actor: staticActors )
   {
      actor->tick( deltaTime );
   }

   for( auto& actor: movableActors )
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

void GameScene::init()
{
   std::sort( staticActors.begin(), staticActors.end(),
              []( const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b ) {
                 return a->getPosition().y < b->getPosition().y;
              }
   );
}

const std::vector<std::shared_ptr<Entity>>& GameScene::getStaticEntities() const
{
   return staticActors;
}

