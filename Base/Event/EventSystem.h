//
// Created by dominik on 22.11.25.
//

#ifndef GAME1_EVENTSYSTEM_H
#define GAME1_EVENTSYSTEM_H

#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>
#include "CallbackContainer.h"

/**
 * A simple event system where you can subscribe to events and publish events.
 * Subscription is done by providing a callback function that will be called when the event is published.
 * @tparam T The type of the event that will be published and subscribed to.
 */
class EventSystem
{
   public:
      explicit EventSystem() = default;

      virtual ~EventSystem() = default;

      template<typename T>
      void subscribe( std::function<void( const T& )> callback );

      template<typename T>
      void publish( const T& event );

   private:
      // Stores all subscribers for each event type based on the type index.
      std::unordered_map<std::type_index, std::unique_ptr<ICallbackContainer>> subscribers;
};

// Templated implementation
template<typename T>
void EventSystem::subscribe( std::function<void( const T& )> callback )
{
   // Get the type index of the event type T
   std::type_index index = std::type_index( typeid( T ) );

   if( subscribers.find( index ) == subscribers.end() )
   {
      subscribers[ index ] = std::make_unique<CallbackContainer<T>>();
   }

   // Cast to a container reference of a concrete type from the found container (it->second)
   auto& container = static_cast<CallbackContainer<T>&>( *subscribers[ index ] );
   container.callbackContainer.push_back( callback );
}

template<typename T>
void EventSystem::publish( const T& event )
{
   std::type_index index = std::type_index( typeid( T ) );

   auto it = subscribers.find( index );

   if( it == subscribers.end() )
      return;

   auto& container = static_cast<CallbackContainer<T>&>( *it->second );

   for( auto& callback: container.callbackContainer )
      callback( event );
}

#endif //GAME1_EVENTSYSTEM_H
