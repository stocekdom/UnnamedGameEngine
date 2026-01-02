//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_BUILDING_H
#define GAME1_BUILDING_H

#include "BuildingType.h"
#include "../../../Base/GameMap/MapTile.h"

class Building : public Actor
{
   public:
      Building( REQ_ARGS, const ActorParams& params );

      // TODO add a whole context instead of just on tile
      /**
       * Checks if the building can be placed on a tile
       * @param tile The tile to be tested
       * @return If a building can be placed on a tile
       */
      virtual bool canBePlaced( const std::shared_ptr<MapTile>& tile );

      /**
       * Runs a necessary setup for the building after it's been placed on a tile
       * @param tile A map tile this building is placed on
       */
      virtual void onPlaced( const std::shared_ptr<MapTile>& tile );

      virtual BuildingType getType() = 0;
};

#endif //GAME1_BUILDING_H
