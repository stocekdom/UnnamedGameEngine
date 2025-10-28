//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_GAME_H
#define GAME1_GAME_H

#include "Scene.h"
#include "Renderer.h"
#include "CollisionSystem.h"

class Game
{
   public:
      void start();

   private:
      GameScene scene;
      Renderer renderer;
      CollisionSystem collisionSystem;
};

#endif //GAME1_GAME_H
