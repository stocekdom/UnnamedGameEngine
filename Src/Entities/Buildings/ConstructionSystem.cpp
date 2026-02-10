//
// Created by dominik on 08.02.26.
//

#include "ConstructionSystem.h"
#include "Building.h"
#include "../../../Base/GameContext.h"

void ConstructionSystem::init( GameContext* context )
{
   context_ = context;
}

void ConstructionSystem::onStart()
{
}

void ConstructionSystem::update( float dt )
{
}

bool ConstructionSystem::canConstruct( const std::shared_ptr<Building>& building, const std::shared_ptr<MapTile>& tile ) const
{
   if( !building->canBePlaced( tile ) )
      return false;

   const auto& costs = Buildings::BuildingCostManager::getCost( building->getType() );

   return std::ranges::all_of( costs, [this]( const auto& req ) {
      auto currentAmount = context_->inventorySystem->getAmount(
         context_->playerEntity,
         Resources::ResourceManager::getResourceId( req.resourceId ) );
      return currentAmount >= req.amount;
   } );
}

bool ConstructionSystem::tryConstruct( std::shared_ptr<Building>& building, std::shared_ptr<MapTile>& tile,
                                       const TileIndex& index ) const
{
   if( !building->canBePlaced( tile ) || !canConstruct( building, tile ) )
      return false;

   const auto& costs = Buildings::BuildingCostManager::getCost( building->getType() );

   for( const auto& req: costs )
   {
      auto ret = context_->inventorySystem->removeItem( context_->playerEntity,
                                                        Resources::ResourceManager::getResourceId( req.resourceId ),
                                                        req.amount );
      // This shouldn't happen since we checked the resources with canConstruct
      if( ret != req.amount )
         LOG_ERROR( "Logical code error: Not enough resources to build building after checking amount" );
   }

   tile->setBuilding( building );
   building->onPlaced( tile );
   context_->gameMapSystem->discoverTiles( index, DISCOVER_RADIUS_ON_BUILD );

   context_->scene->removeComponent<OverlaySpriteComponent>( building->getEntityId() );
   context_->scene->addComponent<SpriteComponent>( building->getEntityId(),
                                                   Buildings::BuildingSpritesManager::getBuildingTexture(
                                                      building->getType() ), SpriteMobility::STATIC,
                                                   sf::Vector2f{ 0.5f, 1.f } );
   return true;
}
