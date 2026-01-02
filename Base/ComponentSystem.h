//
// Created by dominik on 21.12.25.
//

#ifndef GAME1_COMPONENT_SYSTEM_H
#define GAME1_COMPONENT_SYSTEM_H

#include "Entity.h"
#include "System.h"

class ComponentSystem : public System
{
   public:
      // TODO these method check internally if the entity has the component type and all systems will be called for each change.
      // This is O(1) but we could use templates and type erased callbacks and only react to specific types

      /**
       * Lifecycle hook called when an entity is destroyed, but before it's components are deleted
       * This adds an option to do logical cleanup on components that will be erased
       * @param entity The id of deleted entity
       */
      virtual void onBeforeComponentsDestroyed( Entity entity ) = 0;

      /**
       * Empty hook for adding a component
       * Each system can define a specialization for a specific type
       * @param entity The id of entity which got it's component added
       */
      virtual void onComponentAdded( Entity entity ) = 0;

      // Add after component destroyed cleanup if necessary
      //virtual void onEntityDestroyed( Entity entity ) = 0;
};
#endif //GAME1_COMPONENT_SYSTEM_H
