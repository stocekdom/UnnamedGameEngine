//
// Created by dominik on 08.12.25.
//

#ifndef GAME1_ITEMEVENTS_H
#define GAME1_ITEMEVENTS_H

#include "../Entity.h"
#include <string>

struct BaseInventoryItemChanged
{
   Entity entityId = 0;
   const std::string& itemId = "";
   unsigned int amount = 0;
   unsigned int currentAmount = 0;
};

struct InventoryItemRemoved : BaseInventoryItemChanged
{
   unsigned int removedAmount = 0;
};

struct InventoryItemAdded : BaseInventoryItemChanged{};

struct PlayerInventoryItemRemoved : InventoryItemRemoved{};
struct PlayerInventoryItemAdded : InventoryItemAdded{};
#endif //GAME1_ITEMEVENTS_H
