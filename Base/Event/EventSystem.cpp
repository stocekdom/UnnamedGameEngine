//
// Created by dominik on 22.11.25.
//
#include "EventSystem.h"

template<typename T>
void EventSystem::subscribe( std::function<void( T& )> callback )
{
   // Get the type index of the event type T
   std::type_index index = std::type_index( typeid( T ) );

   auto it = subscribers.find( index );

   if( it == subscribers.end() )
   {
      subscribers[ index ] = std::make_unique<CallbackContainer<T>>();
   }

   // Cast to a container reference of a concrete type from the found container (it->second)
   auto& container = static_cast<CallbackContainer<T>&>( *it->second );
   container.callbackContainer.push_back( callback );
}

template<typename T>
void EventSystem::publish( T& event )
{
   std::type_index index = std::type_index( typeid( T ) );

   auto it = subscribers.find( index );

   if( it == subscribers.end() )
      return;

   auto& container = static_cast<CallbackContainer<T>&>( *it->second );

   for( auto& callback : container.callbackContainer )
       callback( event );
}