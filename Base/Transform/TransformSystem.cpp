//
// Created by dominik on 21.12.25.
//

#include "TransformSystem.h"
#include "../Core/Math.h"
#include "../GameContext.h"

TransformSystem::TransformSystem() : transformComponentContainer( nullptr ), needsSorting( false )
{
}

void TransformSystem::init( GameContext* context )
{
   context->scene->getComponentRegistry().registerComponentType<TransformComponent>();
   transformComponentContainer = context->scene->getComponentRegistry().getComponentContainer<TransformComponent>();
}

void TransformSystem::update( float dt )
{
   resolveLoop();
}

void TransformSystem::onStart()
{
   // Resolve all dirty transforms on the start so other systems have valid transform before the first frame
   resolveLoop();
}

void TransformSystem::onComponentAdded( Entity entity )
{
   if( !transformComponentContainer->hasComponent( entity ) )
      return;

   // Properly connect to the parent
   auto& currentEntity = transformComponentContainer->getComponent( entity );

   // NOTE this bypasses sorting inside changeParent because we have an invariant that component container adds elements to the end of the storage
   // Also the parent must already exists, otherwise getComponent ends with an error, so there should be no problem with the order
   if( currentEntity.parent != INVALID_ENTITY )
   {
      TransformComponent& parentEntity = transformComponentContainer->getComponent( currentEntity.parent );
      addChildToParent( parentEntity, entity );
      currentEntity.setDirty();
      currentEntity.hierarchyDepth = parentEntity.hierarchyDepth + 1;
   }
}

void TransformSystem::changeParent( Entity entity, Entity newParent )
{
   auto& currentEntity = transformComponentContainer->getComponent( entity );

   if( currentEntity.parent != INVALID_ENTITY )
   {
      TransformComponent& oldParent = transformComponentContainer->getComponent( currentEntity.parent );
      disconnectParentChild( oldParent, entity );
   }

   currentEntity.parent = newParent;
   currentEntity.setDirty();

   // This makes the element a new root with depth 0. But its children are still sorted correctly relatively to the parent (partial order)
   if( newParent == INVALID_ENTITY )
      return;

   // Changing parent to an existing entity adds it as its child which can break the order, so we need to resort
   needsSorting = true;
   TransformComponent& newParentEntity = transformComponentContainer->getComponent( newParent );

   // Handle the case where the parent doesn't have children yet
   if( newParentEntity.firstChild == INVALID_ENTITY )
   {
      newParentEntity.firstChild = entity;
      newParentEntity.lastChild = entity;
   }
   else
   {
      addChildToParent( newParentEntity, entity );
   }
}

void TransformSystem::onBeforeComponentsDestroyed( Entity entity )
{
   // TODO this currently detaches the children. In the future the scene should cascade delete the entities owning the children. Some hierarchical systems need to implement collect tree method to get ids to delete

   if( !transformComponentContainer->hasComponent( entity ) )
      return;

   TransformComponent& deletedEntity = transformComponentContainer->getComponent( entity );

   // Rewire the children and make them dirty.
   auto child = deletedEntity.firstChild;

   while( child != INVALID_ENTITY )
   {
      auto& childTransform = transformComponentContainer->getComponent( child );
      child = childTransform.nextSibling;
      childTransform.parent = INVALID_ENTITY;
      childTransform.nextSibling = INVALID_ENTITY;
      childTransform.hierarchyDepth = 0;
      childTransform.setDirty();
   }

   // Remove entity from its parent
   if( deletedEntity.parent != INVALID_ENTITY )
      disconnectParentChild( transformComponentContainer->getComponent( deletedEntity.parent ), entity );

   needsSorting = true;
}

// Pointer is used since the parent doesn't have to be defined, but the dirty transform needs to be bound to something with a reference
// This also prevents having to search for the parent by id
void TransformSystem::resolveDirtyTransform( TransformComponent& transform )
{
   if( transform.parent == INVALID_ENTITY )
   {
      // No parent case
      transform.globalPosition = transform.localPosition;
      transform.globalScale = transform.localScale;
      transform.globalRotation = transform.localRotation;
      transform.hierarchyDepth = 0;
   }
   else
   {
      TransformComponent& parentTransform = transformComponentContainer->getComponent( transform.parent );
      // Update cached global transform that's relative to the parent
      transform.globalPosition = Math::parentRelativeToWorldPosition( parentTransform.globalPosition,
                                                                      parentTransform.globalRotation,
                                                                      parentTransform.globalScale,
                                                                      transform.localPosition );
      transform.globalRotation = parentTransform.globalRotation + transform.localRotation;
      transform.globalScale.x = parentTransform.globalScale.x * transform.localScale.x;
      transform.globalScale.y = parentTransform.globalScale.y * transform.localScale.y;
      transform.hierarchyDepth = parentTransform.hierarchyDepth + 1;
   }
}

void TransformSystem::resolveLoop()
{
   if( needsSorting )
   {
      transformComponentContainer->sort( []( const TransformComponent& a, const TransformComponent& b ) {
         return a.hierarchyDepth < b.hierarchyDepth;
      } );
      needsSorting = false;
   }

   for( auto& transform: *transformComponentContainer )
   {
      auto parentDirty = transform.parent != INVALID_ENTITY &&
                         transformComponentContainer->getComponent( transform.parent ).isTransformDirty();
      if( transform.isTransformDirty() || parentDirty )
      {
         transform.setDirty();
         resolveDirtyTransform( transform );
      }
   }

   // Reset flags
   for( auto& transform: *transformComponentContainer )
      transform.setUndirty();
}

void TransformSystem::addChildToParent( TransformComponent& parent, Entity child )
{
   // Handle the case where the parent doesn't have children yet
   if( parent.firstChild == INVALID_ENTITY )
   {
      parent.firstChild = child;
      parent.lastChild = child;
   }
   else
   {
      auto& lastChild = transformComponentContainer->getComponent( parent.lastChild );
      lastChild.nextSibling = child;
      parent.lastChild = child;
   }
}

void TransformSystem::disconnectParentChild( TransformComponent& oldParent, Entity entity ) const
{
   auto child = oldParent.firstChild;
   auto prevChild = INVALID_ENTITY;

   // Iterate over children
   while( child != INVALID_ENTITY && child != entity )
   {
      prevChild = child;
      auto& childComponent = transformComponentContainer->getComponent( child );
      child = childComponent.nextSibling;
   }

   if( child == INVALID_ENTITY )
   {
      LOG_WARNING( "Couldn't disconnect child " + std::to_string( entity ) + " from parent. Entity isn't it's child " );
      return;
   }

   auto& childComponent = transformComponentContainer->getComponent( child );

   // Case where the entity is first child
   if( prevChild == INVALID_ENTITY )
   {
      oldParent.firstChild = childComponent.nextSibling;
   }
   else
   {
      auto& prevChildComponent = transformComponentContainer->getComponent( prevChild );
      prevChildComponent.nextSibling = childComponent.nextSibling;
   }

   // Here child == entity
   childComponent.nextSibling = INVALID_ENTITY;
   childComponent.parent = INVALID_ENTITY;
   childComponent.hierarchyDepth = 0;
   childComponent.setDirty();

   if( entity == oldParent.lastChild )
      oldParent.lastChild = prevChild;
}
