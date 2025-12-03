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

class UIElement;
class Entity;
class GameMap;
class GameContext;

class GameScene
{
   public:

      GameScene();

      ~GameScene() = default;

      void addEntityToScene( const std::shared_ptr<Entity>& actor );

      void deleteEntityById( const UUID& id );

      void addOverlayEntityToScene( const std::shared_ptr<Entity>& actor );

      void deleteOverlayEntityById( const UUID& id );

      void addUIRootComponent( const std::shared_ptr<UIElement>& root );

      [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& getStaticEntities() const;

      [[nodiscard]] const std::vector<std::shared_ptr<Observer>>& getObservers() const;

      void addObserver( const std::shared_ptr<Observer>& observer );

      void addGameMap( const std::shared_ptr<GameMap>& gameMap );

      // Since the scene stores UI elements and map for now, we need to handle click events.
      void onLeftClick( const sf::Vector2i& position );

      void onStart( sf::RenderWindow& window, std::shared_ptr<GameContext>& context );

      void updateFixed( float fixedDt );

      void update( float deltaTime );

      void renderScene( sf::RenderTarget& target, const Renderer& renderer );

      void moveCamera( const sf::Vector2f& delta );

      void zoomCamera( float zoom );

   private:
      // Window, view
      sf::RenderWindow* mainWindow = nullptr;
      std::shared_ptr<sf::View> mainView;
      std::shared_ptr<sf::View> uiView;
      // ===================================
      // UI
      std::shared_ptr<UIElement> uiRoot;
      //========================================
      // Map
      std::shared_ptr<GameMap> map;
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
};

#endif //GAME1_SCENE_H
