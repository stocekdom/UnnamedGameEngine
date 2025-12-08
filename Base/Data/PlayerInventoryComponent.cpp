//
// Created by dominik on 08.12.25.
//
#include "PlayerInventoryComponent.h"
#include "../GameContext.h"
#include "ItemEvents.h"

void PlayerInventoryComponent::onStart( GameContext* context )
{
   contextPtr = context;
}

bool PlayerInventoryComponent::addItem( const std::string& id, unsigned int amount )
{
   auto ret = InventoryComponent::addItem( id, amount );

   // Only broadcast event if item was added successfully.
   if( ret )
      contextPtr->eventSystem->publish( PlayerInventoryItemAdded{ id, amount, getAmount( id ) } );

   return ret;
}

unsigned int PlayerInventoryComponent::removeItem( const std::string& id, unsigned int amount )
{
   auto realRemovedAmount = InventoryComponent::removeItem( id, amount );
   contextPtr->eventSystem->publish( PlayerInventoryItemRemoved{ id, amount, realRemovedAmount, getAmount( id ) } );
   return realRemovedAmount;
}
