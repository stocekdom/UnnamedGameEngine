//
// Created by dominik on 05.12.25.
//
#include "ItemRegistry.h"

ItemRegistry::ItemRegistry( const std::unordered_map<std::string, ItemDefinition>& defs ) : definitions( defs )
{
}

ItemRegistry::ItemRegistry( std::unordered_map<std::string, ItemDefinition>&& defs ) : definitions( std::move( defs ) )
{
}

const std::unordered_map<std::string, ItemDefinition>& ItemRegistry::getDefinitions()
{
   return definitions;
}

const ItemDefinition* ItemRegistry::getDefinition( const std::string& id )
{
   auto it = definitions.find( id );

   if( it == definitions.end() )
      return nullptr;

   return &it->second;
}

void ItemRegistry::addDefinition( const ItemDefinition& definition )
{
   definitions.emplace( definition.id, definition );
}
