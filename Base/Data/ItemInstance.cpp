//
// Created by dominik on 06.12.25.
//
#include <stdexcept>
#include "ItemInstance.h"

// TODO switch to const reference instead of pointer to avoid null checks?
ItemInstance::ItemInstance( unsigned int amount, const ItemDefinition* definition ) : itemAmount( amount ),
                                                                                      definition( definition )
{
   // TODO log error
   if( definition == nullptr )
      throw std::invalid_argument( "ItemDefinition cannot be null" );
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

void ItemInstance::addAmount( unsigned int amount )
{
   this->itemAmount += amount;
}

unsigned int ItemInstance::removeAmount( unsigned int amount )
{
   auto toRemove = std::min( itemAmount, amount );
   itemAmount -= toRemove;
   return toRemove;
}

