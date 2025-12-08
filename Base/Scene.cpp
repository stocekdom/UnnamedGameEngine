//
// Created by dominik on 03.10.25.
//
#include "Scene.h"
#include "Entity/Entity.h"
#include "UI/UIElement.h"

void GameScene::addEntityToScene( const std::shared_ptr<Entity>& actor )
{
   switch( actor->getSpawnCategory() )
   {
      case SpawnCategory::OVERLAY:
         overlayActors.push_back( actor );
         break;
      case SpawnCategory::WORLD:
         spawnWorldActor( actor );
         break;
   }
}

void GameScene::deleteEntityById( const UUID& id )
{
   // TODO switch to ECS
   // Currently, we use vectors for entities, so searching is O(n). This slightly improves performance because user is most likely to delete static entities (houses, trees, etc).
   for( int i = 0; i < staticActors.size(); ++i )
      if( staticActors[ i ]->getId() == id )
      {
         staticActors.erase( staticActors.begin() + i );
         return;
      }

   for( int i = 0; i < movableActors.size(); ++i )
      if( movableActors[ i ]->getId() == id )
      {
         movableActors.erase( movableActors.begin() + i );
         return;
      }
}

void GameScene::deleteOverlayEntityById( const UUID& id )
{
   // Swap and pop since we don't care about order
   for( int i = 0; i < overlayActors.size(); ++i )
      if( overlayActors[ i ]->getId() == id )
      {
         std::swap( overlayActors[ i ], overlayActors.back() );
         overlayActors.pop_back();
         return;
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
      actor->tick( deltaTime );

   for( auto& actor: movableActors )
      actor->tick( deltaTime );

   for( auto& actor: overlayActors )
      actor->tick( deltaTime );
}

sf::Vector2f GameScene::getWorldCoordinates( const sf::Vector2i& screenCoords )
{
   return mainWindow->mapPixelToCoords( screenCoords, *mainView );
}

const std::vector<std::shared_ptr<Observer>>& GameScene::getObservers() const
{
   return observers;
}

void GameScene::addObserver( const std::shared_ptr<Observer>& observer )
{
   observers.push_back( observer );
}

void GameScene::onStart( sf::RenderWindow& window )
{
   // TODO make window smart pointer in the game class
   mainWindow = &window;
   mainView = std::make_shared<sf::View>( window.getDefaultView() );

   // TODO simple Y sorting. Use AABB for better quality and precision
   std::sort( staticActors.begin(), staticActors.end(),
              []( const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b ) {
                 return a->getPosition().y < b->getPosition().y;
              }
   );

   onStartCalled = true;
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

   // Draw overlay entities
   for( auto& actor: overlayActors )
      if( actor->isVisible() )
         renderer.render( actor->getDrawable(), target );
}

void GameScene::moveCamera( const sf::Vector2f& delta )
{
   mainView->move( delta );
}

void GameScene::zoomCamera( float zoom )
{
   mainView->zoom( zoom );
}

void GameScene::spawnWorldActor( const std::shared_ptr<Entity>& actor )
{
   switch( actor->getMobility() )
   {
      case Mobility::STATIC:
         if( onStartCalled )
         {
            auto it = std::lower_bound( staticActors.begin(), staticActors.end(), actor,
                                        []( const std::shared_ptr<Entity>& a, const std::shared_ptr<Entity>& b ) {
                                           return a->getPosition().y < b->getPosition().y;
                                        } );

            staticActors.insert( it, actor );
         }
         else
         {
            staticActors.push_back( actor );
         }

         break;
      case Mobility::MOVABLE:
         movableActors.push_back( actor );
         break;
   }
}
