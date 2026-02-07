//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_PEASANTHOUSE_H
#define GAME1_PEASANTHOUSE_H

#include "../LandBuilding.h"

// TODO add house logic
class PeasantHouse : public LandBuilding
{
   public:
      explicit PeasantHouse( REQ_ARGS, const ActorParams& params );

      bool canBePlaced( const std::shared_ptr<MapTile>& tile ) override;

      Buildings::BuildingType getType() override;
};

#endif //GAME1_PEASANTHOUSE_H
