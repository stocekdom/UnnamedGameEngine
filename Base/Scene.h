//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_SCENE_H
#define GAME1_SCENE_H

#include <vector>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "Entity/Actor.h"
#include "../Controllers/IController.h"
#include "Observers/Observer.h"

class GameScene
{
   public:

      [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& getActors() const;

      void addEntityToScene( std::shared_ptr<Entity> actor );

      [[nodiscard]] const std::vector<std::shared_ptr<Entity>>& getTickableActors() const;

      void addTickableEntityToScene( std::shared_ptr<Entity> tickable );

      void addController( std::unique_ptr<IController> controller );

      [[nodiscard]] const std::vector<std::unique_ptr<IController>>& getControllers() const;

      [[nodiscard]] const std::vector<std::shared_ptr<Observer>>& getObservers() const;

      void addObserver( std::shared_ptr<Observer> observer );

      void handleInput( sf::Event event );

      void updateFixed( float fixedDt );

      void update( float deltaTime );

   private:
      std::vector<std::shared_ptr<Entity>> actors;
      std::vector<std::shared_ptr<Entity>> tickableActors;
      std::vector<std::unique_ptr<IController>> controllers;
      std::vector<std::shared_ptr<Observer>> observers;
};

#endif //GAME1_SCENE_H
