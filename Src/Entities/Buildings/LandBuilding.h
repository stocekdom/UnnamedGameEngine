//
// Created by dominik on 07.02.26.
//

#ifndef GAME1_LANDBUILDING_H
#define GAME1_LANDBUILDING_H
#include "Building.h"

class LandBuilding : public Building
{
   public:
      LandBuilding( Entity id, GameContext* context, const ActorParams& params )
         : Building( id, context, params )
      {
      }

      bool canBePlaced( const std::shared_ptr<MapTile>& tile ) override
      {
         return Building::canBePlaced( tile ) && tile->getType() == Tile::Land;
      }
};
#endif //GAME1_LANDBUILDING_H
