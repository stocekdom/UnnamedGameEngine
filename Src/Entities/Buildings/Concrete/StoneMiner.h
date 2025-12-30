//
// Created by dominik on 16.12.25.
//

#ifndef GAME1_STONEMINER_H
#define GAME1_STONEMINER_H
#include "../Building.h"
#include "../../ResourceActor.h"

// TODO generalize into house, producer, etc.. so we dont have a class for each specific building
class StoneMiner : public Building
{
   public:
      explicit StoneMiner( REQ_ARGS, const ActorParams& params );

      bool canBePlaced( const std::shared_ptr<MapTile>& tile ) override;

      void onPlaced( const std::shared_ptr<MapTile>& tile ) override;

 private:
      GameContext* context_;
      TimerHandle harvestTimer;
      std::weak_ptr<ResourceActor> resource;

      //void harvestResource();
};

#endif //GAME1_STONEMINER_H