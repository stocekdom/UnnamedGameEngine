//
// Created by dominik on 20.12.25.
//

#include "EntityManager.h"

#include <algorithm>
#include <limits>

#include "Logging/Logger.h"

EntityManager::EntityManager()
{
   availableEntityIds.push_back( lastCreatedEntityId + 1 );
}

Entity EntityManager::createEntity()
{
   if( availableEntityIds.front() == std::numeric_limits<Entity>::max() )
      LOG_ERROR( "Cannot create entity. Maximum number of entities reached." );

   auto id = availableEntityIds.front();
   availableEntityIds.pop_front();

   // If there are no more ids we need to add a new one which want's used yet.
   if( availableEntityIds.empty() )
   {
      // Push back since deletion can add lower ids to the front which we want to use first
      availableEntityIds.push_back( id + 1 );
      lastCreatedEntityId++;
   }

   ++livingEntitiesCount;
   return id;
}

bool EntityManager::deleteEntity( const Entity entity )
{
   if( entity >= lastCreatedEntityId )
   {
      LOG_INFO( "Deletion of invalid entity id: " + std::to_string( entity ) );
      return false;
   }

   // For deleted ids, act as a stack to use them earlier
   availableEntityIds.push_front( entity );
   --livingEntitiesCount;
   return true;
}

bool EntityManager::exists( Entity entity )
{
   if( entity >= lastCreatedEntityId )
      return false;

   // First check if the id is available
   return std::ranges::all_of( availableEntityIds, [entity]( auto id ) { return id != entity; } );
}
