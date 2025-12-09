//
// Created by dominik on 06.12.25.
//
#include "InventoryComponent.h"
#include "../GameContext.h"

void InventoryComponent::onStart( GameContext* context )
{
   context_ = context;
}

bool InventoryComponent::addItem( const std::string& id, unsigned int amount )
{
   // Only add needs to check the definition if the item is not already in the inventory.
   // O(1) lookup.
   auto def = context_->itemRegistry->getDefinition( id );
   if( def == nullptr )
      return false;

   // TODO switch to unordered_map if performance is an issue
   for( auto& item: inventory )
      if( item.getInstanceId() == id )
      {
         item.addAmount( amount );
         return true;
      }

   inventory.emplace_back( amount, def );
   return true;
}

unsigned int InventoryComponent::removeItem( const std::string& id, unsigned int amount )
{
   for( auto& item: inventory )
      if( item.getInstanceId() == id )
         return item.removeAmount( amount );

   return 0;
}

unsigned int InventoryComponent::getAmount( const std::string& id )
{
   for( auto& item: inventory )
      if( item.getInstanceId() == id )
         return item.getAmount();

   return 0;
}

