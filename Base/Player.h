//
// Created by dominik on 07.12.25.
//

#ifndef GAME1_PLAYER_H
#define GAME1_PLAYER_H

#include "Entity/FunctionalEntity.h"

class Player : public FunctionalEntity
{
   public:
      Player( Entity id, GameContext* context )
         : FunctionalEntity( id, context )
      {
      }

      void onStart( GameContext* context ) override {}

      void tick( float deltaTime ) override {}
};

#endif //GAME1_PLAYER_H
