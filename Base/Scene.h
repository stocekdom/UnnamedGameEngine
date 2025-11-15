//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_SCENE_H
#define GAME1_SCENE_H

#include <vector>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "Input/Controller.h"
#include "Observers/Observer.h"
#include "Entity/Entity.h"
#include "../Entities/GameMap.h"

class GameScene
{
   public:

      [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& getActors() const;

      void addEntityToScene( const std::shared_ptr<Entity>& actor );

      [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& getTickableActors() const;

      void addTickableEntityToScene( const std::shared_ptr<Entity>& tickable );

      [[nodiscard]] const std::vector<std::shared_ptr<Observer>>& getObservers() const;

      void addObserver( const std::shared_ptr<Observer>& observer );

      void addGameMap( const std::shared_ptr<GameMap>& gameMap );

      // Since the scene stores UI elements and map for now, we need to handle click events.
      void handleLeftClick( const sf::Vector2f& position );

      void updateFixed( float fixedDt );

      void update( float deltaTime );

   private:
      std::shared_ptr<GameMap> map;
      std::vector<std::shared_ptr<Entity>> actors;
      std::vector<std::shared_ptr<Entity>> tickableActors;
      std::vector<std::shared_ptr<Observer>> observers;
};

#endif //GAME1_SCENE_H
