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
      sf::RenderWindow* mainWindow = nullptr;
      std::shared_ptr<sf::View> mainView;
      std::shared_ptr<sf::View> uiView;
      std::shared_ptr<UIElement> uiRoot;
      std::shared_ptr<GameMap> map;
      std::vector<std::shared_ptr<Entity>> staticActors;
      std::vector<std::shared_ptr<Entity>> movableActors;
      // We need to be careful with the lifetime and when deleting entities.
      // TODO isn't easy to delete certain entities from the scene. Need ids for entities.
      std::vector<Entity*> tickableActors;
      std::vector<std::shared_ptr<Observer>> observers;
};

#endif //GAME1_SCENE_H
