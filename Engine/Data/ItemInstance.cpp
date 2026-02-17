//
// Created by dominik on 06.12.25.
//
#include "../Logging/Logger.h"
#include "ItemInstance.h"

// TODO switch to const reference instead of pointer to avoid null checks?
ItemInstance::ItemInstance( const ItemDefinition* definition, unsigned int amount ) : itemAmount( amount ),
   definition( definition )
{
   if( definition == nullptr )
      LOG_ERROR( "ItemDefinition inside ItemInstance is null" );
}

const std::string& ItemInstance::getInstanceId() const
{
   return definition->id;
}

ItemCategory ItemInstance::getItemCategory() const
{
   return definition->category;
}

unsigned int ItemInstance::getAmount() const
{
   return itemAmount;
}

unsigned int ItemInstance::addAmount( unsigned int amount )
{
   this->itemAmount += amount;
   return this->itemAmount;
}

unsigned int ItemInstance::removeAmount( unsigned int amount )
{
   auto toRemove = std::min( itemAmount, amount );
   itemAmount -= toRemove;
   return toRemove;
}
