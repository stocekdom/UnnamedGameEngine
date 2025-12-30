//
// Created by dominik on 03.12.25.
//

#include "PeasantHouse.h"

PeasantHouse::PeasantHouse( Entity id, GameScene* scene, const ActorParams& params )
   : Building( id, scene, params )
{
}

bool PeasantHouse::canBePlaced( const std::shared_ptr<MapTile>& tile )
{
   // Houses can't override resources and be placed on tiles with a resource
   return Building::canBePlaced( tile ) && tile->getResourceType() == Resources::ITEM_NONE;
}
