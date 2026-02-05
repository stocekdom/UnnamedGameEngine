//
// Created by dominik on 03.12.25.
//

#include "Building.h"
#include "../../../Base/GameMap/MapTile.h"

Building::Building( Entity id, GameContext* context, const ActorParams& params )
   : Actor( id, context, params )
{
}

bool Building::canBePlaced( const std::shared_ptr<MapTile>& tile )
{
   return !tile->isOccupied();
}

void Building::onPlaced( const std::shared_ptr<MapTile>& tile )
{
}
