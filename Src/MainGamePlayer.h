//
// Created by dominik on 06.02.26.
//

#ifndef GAME1_MAINGAMEPLAYER_H
#define GAME1_MAINGAMEPLAYER_H

#include "../Base/Player.h"
#include "../Base/Data/InventoryComponent.h"
#include "../Base/Tags/Tags.h"

class MainGamePlayer : public Player
{
   public:
      MainGamePlayer( Entity id, GameContext* context )
         : Player( id, context )
      {
         context->scene->getComponentRegistry().addComponent<InventoryComponent>( id );
         context->scene->getComponentRegistry().addComponent<PlayerTag>( id );
      }
};

#endif //GAME1_MAINGAMEPLAYER_H
