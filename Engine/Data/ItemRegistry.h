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

      explicit ItemRegistry( const std::unordered_map<std::string, ItemDefinition>& itemDefinitions );

      explicit ItemRegistry( std::unordered_map<std::string, ItemDefinition>&& itemDefinitions );

      const std::unordered_map<std::string, ItemDefinition>& getDefinitions();

      /**
       * Gets the item definition based on ID
       * @param id Item ID as a string
       * @return A pointer to the item definition if it exists. Otherwise, returns a nullptr
       */
      const ItemDefinition* getDefinition( const std::string& id );

      void addDefinition( const ItemDefinition& definition );

   protected:
      std::unordered_map<std::string, ItemDefinition> definitions;
};

#endif //GAME1_ITEMREGISTRY_H
