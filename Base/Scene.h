//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_SCENE_H
#define GAME1_SCENE_H

#include "ComponentRegistry.h"
#include "EntityManager.h"
#include "Observers/Observer.h"
#include "Renderer.h"
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>

struct GameContext;
class FunctionalEntity;

class GameScene
{
   public:
      GameScene();

      ~GameScene() = default;

      void init( GameContext* context );

      void onStart( sf::RenderWindow& window );

      /**
       * Creates a functional entity that ticks.
       * Internally handles entity id and registration
       * @tparam T The type of the created entity. Must be a subtype of FunctionalEntity
       * @param args Arguments that get passed to the constructor of T
       * @return Returns a reference to the created entity
       * @note The scene only ticks N times a second in a deterministic loop
       */
      template<typename T, typename... Args>
      std::shared_ptr<T> createTickableFunctionalEntity( Args&&... args );

      /**
       * Creates a functional entity that ticks.
       * Internally handles entity id and registration
       * @tparam T The type of the created entity. Must be a subtype of FunctionalEntity
       * @param args Arguments that get passed to the constructor of T
       * @return Returns a reference to the created entity
       * @note The scene only ticks N times a second in a deterministic loop
       */
      template<typename T, typename... Args>
      std::shared_ptr<T> addFunctionalEntity( Args&&... args );

      // Currently unnamed entities. Entity is only id
      Entity createEntity() const;

      bool deleteEntity( Entity entity );

      bool exists( Entity entity ) const;

      [[nodiscard]] const std::vector<std::shared_ptr<Observer>>& getObservers() const;

      void addObserver( const std::shared_ptr<Observer>& observer );

      [[nodiscard]] sf::Vector2f getWorldCoordinates( const sf::Vector2i& screenCoords ) const;

      void updateFixed( float fixedDt );

      //void renderScene( sf::RenderTarget& target, const Renderer& renderer ) const;

      template<typename TC>
      bool addComponent( Entity entity, TC component );

      template<typename TC, typename... Args>
      bool addComponent( Entity entity, Args&&... args );

      template<typename TC>
      bool removeComponent( Entity entity );

      void moveCamera( const sf::Vector2f& delta ) const;

      void zoomCamera( float zoom ) const;

      ComponentRegistry& getComponentRegistry();

   private:
      GameContext* context_ = nullptr;
      // Window, view
      sf::RenderWindow* mainWindow = nullptr;
      std::shared_ptr<sf::View> mainView;
      // ========================================
      // Registries
      std::unique_ptr<EntityManager> entityManager;
      std::unique_ptr<ComponentRegistry> componentRegistry;

      // ============================================================
      // Entities
      // Here we treat functional entities as components so we can reuse the ComponentContainer(packed array) for faster lookup and deletion
      ComponentContainer<std::shared_ptr<FunctionalEntity>> tickableEntities;
      ComponentContainer<std::shared_ptr<FunctionalEntity>> otherEntities;
      //std::unordered_map<Entity, std::shared_ptr<FunctionalEntity>> tickableEntities;
      //std::unordered_map<Entity, std::shared_ptr<FunctionalEntity>> otherEntities;
      // =======================================
      // Observers
      std::vector<std::shared_ptr<Observer>> observers;
      bool onStartCalled = false;

      void callComponentAdded( Entity entity ) const;

      void callComponentRemoved( Entity entity ) const;

      template<typename T, typename... Args>
      std::shared_ptr<T> createFunctionalEntityImpl( ComponentContainer<std::shared_ptr<FunctionalEntity>>& c, Args&&... args );
};

template<typename T, typename... Args>
std::shared_ptr<T> GameScene::createTickableFunctionalEntity( Args&&... args )
{
   return createFunctionalEntityImpl<T>( tickableEntities, std::forward<Args>( args )... );
}

template<typename T, typename... Args>
std::shared_ptr<T> GameScene::addFunctionalEntity( Args&&... args )
{
   return createFunctionalEntityImpl<T>( otherEntities, std::forward<Args>( args )... );
}

template<typename TC>
bool GameScene::addComponent( Entity entity, TC component )
{
   auto res = componentRegistry->addComponent( entity, component );
   callComponentAdded( entity );
   return res;
}

template<typename TC, typename... Args>
bool GameScene::addComponent( Entity entity, Args&&... args )
{
   auto res = componentRegistry->addComponent<TC>( entity, std::forward<Args>( args )... );
   callComponentAdded( entity );
   return res;
}

template<typename TC>
bool GameScene::removeComponent( Entity entity )
{
   callComponentRemoved( entity );
   return componentRegistry->removeComponent<TC>( entity );
}

template<typename T, typename... Args>
std::shared_ptr<T> GameScene::createFunctionalEntityImpl( ComponentContainer<std::shared_ptr<FunctionalEntity>>& c,
                                                          Args&&... args )
{
   static_assert( std::is_base_of_v<FunctionalEntity, T>,
                  "Cannot create functional entity. T must be a subtype of FunctionalEntity" );

   auto newId = createEntity();
   auto entity = std::make_shared<T>( newId, this, std::forward<Args>( args )... );

   if( !c.addComponent( newId, entity ) )
   {
      LOG_WARNING(
         "Couldn't add functional entity " + std::string( typeid( T ).name() ) + "with id: " + std::to_string( newId ) +
         " to container" );
      return nullptr;
   }

   LOG_DEBUG( "Adding functional entity " + std::string( typeid( T ).name() ) + " with id: " + std::to_string( newId ) )

   // Start the entity if the game is already running
   if( onStartCalled )
      entity->onStart( context_ );

   return entity;
}

#endif //GAME1_SCENE_H
