//
// Created by dominik on 20.12.25.
//

#ifndef GAME1_COMPONENTREGISTRY_H
#define GAME1_COMPONENTREGISTRY_H

#include "Sprite/SpriteComponent.h"
#include "Transform/TransformComponent.h"
#include "ComponentContainer.h"
#include <memory>
#include <typeindex>

class ComponentRegistry
{
   public:
      virtual ~ComponentRegistry() = default;

      template<typename TC>
      bool registerComponentType();

      template<typename TC>
      bool addComponent( Entity entity, TC component );

      template<typename TC, typename... Args>
      bool addComponent( Entity entity, Args&&... args );

      template<typename TC>
      bool removeComponent( Entity entity );

      template<typename TC>
      TC& getComponent( Entity entity );

      template<typename TC>
      bool hasComponent( Entity entity );

      void onEntityDestroyed( Entity entity );

      template<typename TC>
      ComponentContainer<TC>* getComponentContainer();

   private:
      std::unordered_map<std::type_index, std::unique_ptr<IComponentContainer>> registry;

      template<typename TC>
      void checkDependencies( Entity entity );
};

inline void ComponentRegistry::onEntityDestroyed( Entity entity )
{
   for( auto& [ id, container ]: registry )
      container->onEntityDestroyed( entity );
}

template<typename TC>
bool ComponentRegistry::registerComponentType()
{
   std::type_index id = std::type_index( typeid( TC ) );

   auto t = registry.contains( id );
   if( registry.contains( id ) )
   {
      LOG_WARNING( "Component type " + std::string( typeid( TC ).name() ) + " is already registered" );
      return false;
   }

   registry[ id ] = std::make_unique<ComponentContainer<TC>>();
   return true;
}

template<typename TC>
bool ComponentRegistry::addComponent( Entity entity, TC component )
{
   checkDependencies<TC>( entity );
   return getComponentContainer<TC>()->addComponent( entity, component );
}

template<typename TC, typename... Args>
bool ComponentRegistry::addComponent( Entity entity, Args&&... args )
{
   checkDependencies<TC>( entity );
   return getComponentContainer<TC>()->addComponent( entity, std::forward<Args>( args )... );
}

template<typename TC>
bool ComponentRegistry::removeComponent( Entity entity )
{
   return getComponentContainer<TC>()->removeComponent( entity );
}

template<typename TC>
TC& ComponentRegistry::getComponent( Entity entity )
{
   return getComponentContainer<TC>()->getComponent( entity );
}

template<typename TC>
bool ComponentRegistry::hasComponent( Entity entity )
{
   return getComponentContainer<TC>()->hasComponent( entity );
}

template<typename TC>
ComponentContainer<TC>* ComponentRegistry::getComponentContainer()
{
   auto id = std::type_index( typeid( TC ) );

   if( !registry.contains( id ) )
      LOG_ERROR( "Cannot get component container. Component type " + std::string( typeid( TC ).name() ) + " is not registered" );

   return static_cast<ComponentContainer<TC>*>( registry[ id ].get() );
}

template<typename TC>
void ComponentRegistry::checkDependencies( Entity entity )
{
}

template<>
inline void ComponentRegistry::checkDependencies<SpriteComponent>( Entity entity )
{
   if( !hasComponent<TransformComponent>( entity ) )
      addComponent<TransformComponent>( entity );
}

#endif //GAME1_COMPONENTREGISTRY_H
