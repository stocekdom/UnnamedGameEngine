//
// Created by dominik on 03.12.25.
//

#ifndef GAME1_PEASANTHOUSE_H
#define GAME1_PEASANTHOUSE_H

#include "../Building.h"

// TODO add house logic
class PeasantHouse : public Building
{
   public:
      explicit PeasantHouse( REQ_ARGS, const ActorParams& params );

      bool canBePlaced( const std::shared_ptr<MapTile>& tile ) override;
};

#endif //GAME1_PEASANTHOUSE_H
