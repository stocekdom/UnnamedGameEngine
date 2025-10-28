#include "Scene.h"
//
// Created by dominik on 03.10.25.
//
const std::vector<std::shared_ptr<Entity>>& GameScene::getActors() const
{
   return actors;
}

void GameScene::addEntityToScene( std::shared_ptr<Entity> actor )
{
   actors.push_back( std::move( actor ) );
}

const std::vector<std::shared_ptr<Entity>>& GameScene::getTickableActors() const
{
   return tickableActors;
}

void GameScene::addTickableEntityToScene( std::shared_ptr<Entity> tickable )
{
   tickableActors.push_back( std::move( tickable ) );
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
   for( auto& actor: tickableActors )
   {
      actor->tick( deltaTime );
   }
}

void GameScene::addController( std::unique_ptr<IController> controller )
{
   controllers.push_back( std::move( controller ) );
}

const std::vector<std::unique_ptr<IController>>& GameScene::getControllers() const
{
   return controllers;
}

void GameScene::handleInput( sf::Event event )
{
   for( auto& controller: controllers )
   {
      controller->handleInput( event );
   }
}

const std::vector<std::shared_ptr<Observer>>& GameScene::getObservers() const
{
   return observers;
}

void GameScene::addObserver( std::shared_ptr<Observer> observer )
{
   observers.push_back( std::move( observer ) );
}

