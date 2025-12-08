//
// Created by dominik on 05.12.25.
//

#ifndef GAME1_ITEMINSTANCE_H
#define GAME1_ITEMINSTANCE_H

#include "ItemDefinition.h"

class ItemInstance
{
   public:
      ItemInstance( unsigned int amount, const ItemDefinition* definition );

      [[nodiscard]] const std::string& getInstanceId() const;

      [[nodiscard]] ItemCategory getItemCategory() const;

      [[nodiscard]] unsigned int getAmount() const;

      void addAmount( unsigned int amount );

      /**
       * Removes the given amount from the item.
       * @param amount Amount to remove.
       * @return Returns the amount the was removed. If the amount is greater than the amount of the item, the amount of the item is returned.
       */
      unsigned int removeAmount( unsigned int amount );

   private:
      unsigned int itemAmount = 0;
      const ItemDefinition* definition = nullptr;
};

#endif //GAME1_ITEMINSTANCE_H
