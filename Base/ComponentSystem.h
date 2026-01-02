//
// Created by dominik on 21.12.25.
//

#ifndef GAME1_SYSTEM_H
#define GAME1_SYSTEM_H
#include "Entity.h"

struct GameContext;

class System
{
   public:
      virtual ~System() = default;

      /**
       * Lifecycle hook called after all systems have been constructed.
       * Here all systems are alive, and it is safe to use them, but they might not contain any useful data yet
       * @param context The game context
       */
      virtual void init( GameContext* context ) = 0;

      /**
       * Lifecycle hook called when the game is starting
       * It's called before the first frame. Here systems can do necessary operations without having to do them in the first frame
       */
      virtual void onStart() = 0;

      virtual void update( float dt ) = 0;

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
#endif //GAME1_SYSTEM_H
