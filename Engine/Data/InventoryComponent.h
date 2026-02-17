//
// Created by dominik on 05.12.25.
//

#ifndef GAME1_INVENTORYCOMPONENT_H
#define GAME1_INVENTORYCOMPONENT_H

#include "ItemInstance.h"
#include <vector>

struct InventoryComponent
{
   // Don't modify this from anywhere. Use only the InventorySystem API
   std::vector<ItemInstance> inventory;
};

#endif //GAME1_INVENTORYCOMPONENT_H
