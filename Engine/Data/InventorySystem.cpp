//
// Created by dominik on 06.02.26.
//
#include "InventorySystem.h"
#include "ItemEvents.h"
#include "../GameContext.h"
#include "../Tags/Tags.h"

void InventorySystem::init( GameContext* context )
{
   gameContext = context;
   auto& registry = context->scene->getComponentRegistry();
   registry.registerComponentType<InventoryComponent>();

   inventoryContainer = registry.getComponentContainer<InventoryComponent>();
}

void InventorySystem::onStart()
{
}

void InventorySystem::update( float dt )
{
}

void InventorySystem::onBeforeComponentsDestroyed( Entity entity )
{
}

void InventorySystem::onComponentAdded( Entity entity )
{
}

bool InventorySystem::addItem( Entity entityId, const std::string& itemId, unsigned int amount )
{
   // Only add needs to check the definition if the item is not already in the inventory.
   // O(1) lookup.
   auto def = gameContext->itemRegistry->getDefinition( itemId );

   if( !def || !inventoryContainer->hasComponent( entityId ) )
      return false;

   auto& component = inventoryContainer->getComponent( entityId );

   // TODO switch to unordered_map if performance is an issue
   for( auto& item: component.inventory )
      if( item.getInstanceId() == itemId )
      {
         auto currentAmount = item.addAmount( amount );
         handleAfterAdd( entityId, itemId, amount, currentAmount );
         return true;
      }

   component.inventory.emplace_back( amount, def );

   handleAfterAdd( entityId, itemId, amount, amount );
   return true;
}

unsigned int InventorySystem::removeItem( Entity entityId, const std::string& itemId, unsigned int amount )
{
   if( !inventoryContainer->hasComponent( entityId ) )
      return 0;

   for( auto& item: inventoryContainer->getComponent( entityId ).inventory )
      if( item.getInstanceId() == itemId )
      {
         auto removed = item.removeAmount( amount );
         handleAfterRemove( entityId, itemId, amount, removed, item.getAmount() );
         return removed;
      }

   return 0;
}

unsigned int InventorySystem::getAmount( Entity entityId, const std::string& itemId )
{
   if( !inventoryContainer->hasComponent( entityId ) )
      return 0;

   for( auto& item: inventoryContainer->getComponent( entityId ).inventory )
      if( item.getInstanceId() == itemId )
         return item.getAmount();

   return 0;
}

void InventorySystem::handleAfterAdd( Entity entityId, const std::string& itemdId, unsigned int amount,
                                      unsigned int currentAmount ) const
{
   // Special behavior for player classes
   if( gameContext->scene->getComponentRegistry().hasComponent<PlayerTag>( entityId ) )
      gameContext->eventSystem->publish( PlayerInventoryItemAdded{ entityId, itemdId, amount, currentAmount } );
   else
      gameContext->eventSystem->publish( InventoryItemAdded{ entityId, itemdId, amount, currentAmount } );
}

void InventorySystem::handleAfterRemove( Entity entityId, const std::string& itemdId, unsigned int amount,
                                         unsigned int removedAmount, unsigned int currentAmount ) const
{
   if( gameContext->scene->getComponentRegistry().hasComponent<PlayerTag>( entityId ) )
      gameContext->eventSystem->publish( PlayerInventoryItemRemoved{ entityId, itemdId, amount, currentAmount, removedAmount } );
   else
      gameContext->eventSystem->publish( InventoryItemRemoved{ entityId, itemdId, amount, currentAmount, removedAmount } );
}
