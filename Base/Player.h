//
// Created by dominik on 07.12.25.
//

#ifndef GAME1_PLAYER_H
#define GAME1_PLAYER_H

#include <memory>
#include "Data/PlayerInventoryComponent.h"

class Player
{
   public:
      virtual ~Player() = default;

      virtual void onStart( GameContext* context ) = 0;

   private:
      std::unique_ptr<PlayerInventoryComponent> inventory;
};

#endif //GAME1_PLAYER_H
