//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_GAME_H
#define GAME1_GAME_H

#include "Scene.h"
#include "Renderer.h"
#include "Collision/CollisionSystem.h"
#include "TextureManager.h"

// TODO use engine class to store scene, renderer and collision system and use DI
class Game
{
   public:
      void start();

   private:
      GameScene scene;
      Renderer renderer;
      CollisionSystem collisionSystem;
      TextureManager textureManager;
};

#endif //GAME1_GAME_H
