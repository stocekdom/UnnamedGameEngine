//
// Created by dominik on 08.12.25.
//

#ifndef GAME1_ITEMEVENTS_H
#define GAME1_ITEMEVENTS_H

#include <string>

struct PlayerInventoryItemRemoved
{
   const std::string& itemId = "";
   unsigned int amount = 0;
   unsigned int removedAmount = 0;
   unsigned int currentAmount = 0;
};

struct PlayerInventoryItemAdded
{
   const std::string& itemId = "";
   unsigned int amount = 0;
   unsigned int currentAmount = 0;
};

#endif //GAME1_ITEMEVENTS_H
