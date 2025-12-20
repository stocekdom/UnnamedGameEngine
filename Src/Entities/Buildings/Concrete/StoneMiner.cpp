//
// Created by dominik on 16.12.25.
//

#include "StoneMiner.h"

#include "../../../../Base/Logging/Logger.h"

StoneMiner::StoneMiner( SpawnCategory spawnCategory, const sf::Vector2f& position, float rotation, const sf::Vector2f& scale,
                        float height, bool isVisible )
   : Building( spawnCategory, position, rotation, scale, height, isVisible )
{
}

void StoneMiner::onStart( GameContext* context )
{
   sprite.setTexture( context->resourceManager->loadTexture( "Assets/Buildings/stoneMiner.png" ) );
   Building::onStart( context );
   context_ = context;

   // TODO handle pausing if resource is depleted
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

   harvestTimer = context_->timeManager->makeRepeatingTimer( r->getHarvestTime(), [this, r] {
      context_->player->addItem( Resources::ID_ARRAY[ Resources::Resource::ITEM_ROCKS ], r->harvest() );
   } );
}
