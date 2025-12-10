//
// Created by dominik on 05.12.25.
//

#ifndef GAME1_INVENTORYCOMPONENT_H
#define GAME1_INVENTORYCOMPONENT_H

#include "ItemInstance.h"
#include <vector>

struct GameContext;

class InventoryComponent
{
   public:
      virtual ~InventoryComponent() = default;

      virtual void onStart( GameContext* context );

      virtual bool addItem( const std::string& id, unsigned int amount );

      /**
       * Removes the given amount of an item from the inventory.
       * @param id ID of the item to remove.
       * @param amount Amount to remove.
       * @return Returns the amount that was removed. If the amount is greater than the amount of the item, the amount of the item is returned.
       */
      virtual unsigned int removeItem( const std::string& id, unsigned int amount );

      virtual unsigned int getAmount( const std::string& id );

   protected:
      std::vector<ItemInstance> inventory;
      GameContext* context_ = nullptr;
};

#endif //GAME1_INVENTORYCOMPONENT_H
