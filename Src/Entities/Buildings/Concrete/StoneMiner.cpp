//
// Created by dominik on 16.12.25.
//

#include "StoneMiner.h"

#include "../../../../Base/Logging/Logger.h"

// TODO handle pausing if resource is depleted
// TODO add timer component

StoneMiner::StoneMiner( Entity id, GameContext* context, const ActorParams& params )
   : Building( id, context, params )
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

   //                                                          time duration,     callback,                           isRepeating
   context_->scene->addComponent<TimerComponent>( entity, r->getHarvestTime(), [this]() { harvestResource(); }, true );
}

Buildings::BuildingType StoneMiner::getType()
{
   return Buildings::BuildingType::STONE_MINER;
}

void StoneMiner::harvestResource() const
{
   if( auto r = resource.lock() )
      context_->inventorySystem->addItem( context_->playerEntity,
                                          Resources::ResourceManager::getResourceId( Resources::Resource::ITEM_ROCKS ),
                                          r->harvest() );
}
