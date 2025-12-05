//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_SCENE_H
#define GAME1_SCENE_H

#include <vector>
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Observers/Observer.h"
#include "Renderer.h"
#include "Core/UUID.h"

class Entity;
class GameContext;

class GameScene
{
   public:
      ~GameScene() = default;

      void onStart( sf::RenderWindow& window );

      void addEntityToScene( const std::shared_ptr<Entity>& actor );

      void deleteEntityById( const UUID& id );

      // TODO this isn't clean switch to ECS
      void deleteOverlayEntityById( const UUID& id );

      [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& getStaticEntities() const;

      [[nodiscard]] const std::vector<std::shared_ptr<Observer>>& getObservers() const;

      void addObserver( const std::shared_ptr<Observer>& observer );

      sf::Vector2f getWorldCoordinates( const sf::Vector2i& screenCoords );

      void updateFixed( float fixedDt );

      void update( float deltaTime );

      void renderScene( sf::RenderTarget& target, const Renderer& renderer );

      void moveCamera( const sf::Vector2f& delta );

      void zoomCamera( float zoom );

   private:
      // Window, view
      sf::RenderWindow* mainWindow = nullptr;
      std::shared_ptr<sf::View> mainView;
      // ========================================
      // Entities
      // Entities that can't be moved. Sorted in onStart method
      std::vector<std::shared_ptr<Entity>> staticActors;
      std::vector<std::shared_ptr<Entity>> movableActors;
      // Special unordered container for entities which are drawn on top of everything else but are not part of the scene (overlays, temporary entities, editor only)
      std::vector<std::shared_ptr<Entity>> overlayActors;
      // =======================================
      // Observers
      std::vector<std::shared_ptr<Observer>> observers;
      // We need to be careful with the lifetime and when deleting entities.
      // TODO isn't easy to delete certain entities from the scene. Need ids for entities.
      // Helper container of non-owning pointers to actors that tick
      std::vector<Entity*> tickableActors;
      bool onStartCalled = false;

      void spawnWorldActor( const std::shared_ptr<Entity>& actor );
};

#endif //GAME1_SCENE_H
