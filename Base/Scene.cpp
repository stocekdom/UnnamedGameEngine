//
// Created by dominik on 03.10.25.
//

#include "Scene.h"
#include "Entity/FunctionalEntity.h"

/*
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
*/

GameScene::GameScene() : entityManager( std::make_unique<EntityManager>() ),
                         componentRegistry( std::make_unique<ComponentRegistry>() )
{
}

void GameScene::init( GameContext* context )
{
   context_ = context;
}

void GameScene::onStart( sf::RenderWindow& window )
{
   // TODO make window smart pointer in the game class
   mainWindow = &window;
   mainView = std::make_shared<sf::View>( window.getDefaultView() );
   onStartCalled = true;

   for( auto& entity: tickableEntities )
      entity->onStart( context_ );

   for( auto& entity: otherEntities )
      entity->onStart( context_ );
}

void GameScene::updateFixed( float fixedDt )
{
   // ReSharper disable once CppUseElementsView
   for( auto& entity: tickableEntities )
   {
      entity->tick( fixedDt );
   }
}

ComponentRegistry& GameScene::getComponentRegistry()
{
   return *componentRegistry;
}

sf::Vector2f GameScene::getWorldCoordinates( const sf::Vector2i& screenCoords ) const
{
   return mainWindow->mapPixelToCoords( screenCoords, *mainView );
}

Entity GameScene::createEntity() const
{
   return entityManager->createEntity();
}

bool GameScene::deleteEntity( Entity entity )
{
   // Only do operations when the entity was actually present and deleted. One branch can save potential high cost operations
   if( entityManager->deleteEntity( entity ) )
   {
      callComponentRemoved( entity );
      componentRegistry->onEntityDestroyed( entity );

      // TODO add check contains to avoid deleting from both if only one has the entity?
      otherEntities.removeComponent( entity );
      tickableEntities.removeComponent( entity );
      return true;
   }

   return false;
}

bool GameScene::exists( Entity entity ) const
{
   return entityManager->exists( entity ) || tickableEntities.hasComponent( entity ) || otherEntities.hasComponent( entity );
}

const std::vector<std::shared_ptr<Observer>>& GameScene::getObservers() const
{
   return observers;
}

void GameScene::addObserver( const std::shared_ptr<Observer>& observer )
{
   observers.push_back( observer );
}

/*
void GameScene::renderScene( sf::RenderTarget& target, const Renderer& renderer ) const
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
*/

void GameScene::moveCamera( const sf::Vector2f& delta ) const
{
   mainView->move( delta );
}

void GameScene::zoomCamera( float zoom ) const
{
   mainView->zoom( zoom );
}

/*
void GameScene::spawnWorldActor( const std::shared_ptr<Entity>& actor )
{
   switch( actor->getMobility() )
   {
      case Mobility::STATIC:
         if( onStartCalled )
         {
            auto it = std::ranges::lower_bound( staticActors, actor,
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
*/

void GameScene::callComponentAdded( Entity entity ) const
{
   context_->transformSystem->onComponentAdded( entity );
   context_->spriteSystem->onComponentAdded( entity );
   context_->overlaySystem->onComponentAdded( entity );
}

void GameScene::callComponentRemoved( Entity entity ) const
{
   context_->transformSystem->onBeforeComponentsDestroyed( entity );
   context_->spriteSystem->onBeforeComponentsDestroyed( entity );
   context_->overlaySystem->onBeforeComponentsDestroyed( entity );
}