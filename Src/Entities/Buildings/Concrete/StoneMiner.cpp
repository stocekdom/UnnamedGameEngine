//
// Created by dominik on 16.12.25.
//

#include "StoneMiner.h"

#include "../../../../Base/Logging/Logger.h"

// TODO handle pausing if resource is depleted
// TODO add timer component

StoneMiner::StoneMiner( Entity id, GameScene* scene, const ActorParams& params )
   : Building( id, scene, params ), context_( nullptr )
{
}

bool StoneMiner::canBePlaced( const std::shared_ptr<MapTile>& tile )
{
   if( Building::canBePlaced( tile ) )
      return tile->getResourceType() == Resources::Resource::ITEM_ROCKS;

   return false;
}

void StoneMiner::onPlaced( const std::shared_ptr<MapTile>& tile )
{
   Building::onPlaced( tile );
   resource = tile->getResource();

   auto r = resource.lock();

   if( !r )
   {
      LOG_ERROR( "Stone mine placed with invalid tile resource" )
      return;
   }
/*
   harvestTimer = context_->timeManager->makeRepeatingTimer( r->getHarvestTime(), [this, r] {
      context_->player->addItem( Resources::ID_ARRAY[ Resources::Resource::ITEM_ROCKS ], r->harvest() );
   } );*/
}

BuildingType StoneMiner::getType()
{
   return BuildingType::STONE_MINER;
}
