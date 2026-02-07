//
// Created by dominik on 03.12.25.
//

#include "PeasantHouse.h"

PeasantHouse::PeasantHouse( Entity id, GameContext* context, const ActorParams& params )
   : LandBuilding( id, context, params )
{
}

bool PeasantHouse::canBePlaced( const std::shared_ptr<MapTile>& tile )
{
   // Houses can't override resources and be placed on tiles with a resource
   return LandBuilding::canBePlaced( tile ) && tile->getResourceType() == Resources::Resource::ITEM_NONE;
}

Buildings::BuildingType PeasantHouse::getType()
{
   return Buildings::BuildingType::PEASANT_HOUSE;
}
