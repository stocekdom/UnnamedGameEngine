//
// Created by dominik on 05.12.25.
//

#ifndef GAME1_ITEMDEFINITION_H
#define GAME1_ITEMDEFINITION_H

#include <string>

enum class ItemCategory
{
   RESOURCE,
   MONEY,
};

struct ItemDefinition
{
   std::string id;
   std::string name;
   std::string description;
   std::string texturePath;
   ItemCategory category;
   int maxStackSize;
};
#endif //GAME1_ITEMDEFINITION_H
