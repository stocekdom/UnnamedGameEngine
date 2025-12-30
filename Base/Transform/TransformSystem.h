//
// Created by dominik on 21.12.25.
//

#ifndef GAME1_TRANSFORMSYSTEM_H
#define GAME1_TRANSFORMSYSTEM_H

#include "../ComponentContainer.h"
#include "TransformComponent.h"
#include "../System.h"

class TransformSystem : public System
{
   public:
      TransformSystem();

      void init( GameContext* context ) override;

      void update( float dt ) override;

      void onStart() override;

      void onComponentAdded( Entity entity ) override;

      void changeParent( Entity entity, Entity newParent );

      void onBeforeComponentsDestroyed( Entity entity ) override;

   private:
      ComponentContainer<TransformComponent>* transformComponentContainer;
      bool needsSorting;

      void resolveDirtyTransform( TransformComponent& transform );

      void resolveLoop();

      void addChildToParent( TransformComponent& parent, Entity child );

      void disconnectParentChild( TransformComponent& oldParent, Entity entity ) const;
};
#endif //GAME1_TRANSFORMSYSTEM_H
