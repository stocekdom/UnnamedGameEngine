//
// Created by dominik on 06.02.26.
//

#ifndef GAME1_INVENTORYSYSTEM_H
#define GAME1_INVENTORYSYSTEM_H

#include "InventoryComponent.h"
#include "../ComponentSystem.h"
#include "../ComponentContainer.h"
#include "ItemEvents.h"

class InventorySystem : public ComponentSystem
{
   public:
      void init( GameContext* context ) override;

      void onStart() override;

      void update( float dt ) override;

      void onBeforeComponentsDestroyed( Entity entity ) override;

      void onComponentAdded( Entity entity ) override;

      // Inventory API -----------------------------------------------------------------

      virtual bool addItem( Entity entityId, const std::string& itemId, unsigned int amount );

      /**
       * Removes the given amount of an item from the inventory.
       * @param entityId ID of the entity which owns the inventory
       * @param itemId ID of the item to remove.
       * @param amount Amount to remove.
       * @return Returns the amount that was removed. If the amount is greater than the amount of the item, the amount of the item is returned.
       */
      virtual unsigned int removeItem( Entity entityId, const std::string& itemId, unsigned int amount );

      virtual unsigned int getAmount( Entity entityId, const std::string& itemId );

   private:
      GameContext* gameContext = nullptr;
      ComponentContainer<InventoryComponent>* inventoryContainer = nullptr;

      void handleAddEvent( const InventoryItemAdded& data ) const;

      void handleAfterRemove( const InventoryItemRemoved& data ) const;
};

#endif //GAME1_INVENTORYSYSTEM_H
