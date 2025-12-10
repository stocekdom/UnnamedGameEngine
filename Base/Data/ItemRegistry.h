//
// Created by dominik on 05.12.25.
//

#ifndef GAME1_ITEMREGISTRY_H
#define GAME1_ITEMREGISTRY_H

#include "ItemDefinition.h"
#include <unordered_map>

class ItemRegistry
{
   public:
      ItemRegistry() = default;

      explicit ItemRegistry( const std::unordered_map<std::string, ItemDefinition>& defs );

      explicit ItemRegistry( std::unordered_map<std::string, ItemDefinition>&& defs );

      const std::unordered_map<std::string, ItemDefinition>& getDefinitions();

      const ItemDefinition* getDefinition( const std::string& id );

      void addDefinition( const ItemDefinition& definition );

   protected:
      std::unordered_map<std::string, ItemDefinition> definitions;
};

#endif //GAME1_ITEMREGISTRY_H
