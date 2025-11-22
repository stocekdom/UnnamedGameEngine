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
      void subscribe( std::function<void( T& )> callback );

      template<typename T>
      void publish( T& event );

   private:
      // Stores all subscribers for each event type based on the type index.
      std::unordered_map<std::type_index, std::unique_ptr<ICallbackContainer>> subscribers;
};


#endif //GAME1_EVENTSYSTEM_H
