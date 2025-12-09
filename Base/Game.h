//
// Created by dominik on 03.10.25.
//

#ifndef GAME1_GAME_H
#define GAME1_GAME_H

#include "GameContext.h"
#include "Renderer.h"

class PlayerInventoryComponent;

class Game
{
   public:
      Game();

      ~Game() = default;

      void start();

   private:
      // TODO use a player class instead once we have more functinality for it
      std::shared_ptr<PlayerInventoryComponent> player;
      std::shared_ptr<Renderer> renderer;
      std::shared_ptr<GameContext> context;
};

#endif //GAME1_GAME_H
