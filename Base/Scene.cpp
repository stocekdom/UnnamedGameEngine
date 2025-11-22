//
// Created by dominik on 03.10.25.
//
#include "Scene.h"

GameScene::GameScene()
{
   // Make an empty default UI root to avoid nullptr checks
   uiRoot = std::make_shared<UIElement>( sf::Vector2f{ 0.f, 0.f }, 0, false );
}

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

void GameScene::addUIRootComponent( const std::shared_ptr<UIElement>& root )
{
   uiRoot = root;
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

void GameScene::onLeftClick( const sf::Vector2f& position )
{
   if( uiRoot->onClick( position ) )
      return;

   map->onClick( position );
}

void GameScene::init( sf::RenderWindow& window )
{
   mainView = std::make_shared<sf::View>( window.getDefaultView() );
   uiView = std::make_shared<sf::View>( *mainView );

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

void GameScene::renderScene( sf::RenderTarget& target, const Renderer& renderer )
{
   // Draw entities
   // TODO currently only static entities are rendered. Add merging with the movable entities
   target.setView( *mainView );
   for( auto& actor: staticActors )
      if( actor->isVisible() )
         renderer.render( actor->getDrawable(), target );

   // Draw UI tree
   target.setView( *uiView );
   uiRoot->draw( target, renderer );
}

