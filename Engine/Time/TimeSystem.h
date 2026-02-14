//
// Created by dominik on 09.12.25.
//

#ifndef GAME1_TIMESYSTEM_H
#define GAME1_TIMESYSTEM_H

#include "../ComponentSystem.h"
#include "TimerComponent.h"
#include "../ComponentContainer.h"

class TimeSystem : public ComponentSystem
{
   using Callback = std::function<void()>;

   public:
      void init( GameContext* context ) override;

      void onStart() override;

      void onBeforeComponentsDestroyed( Entity entity ) override;

      void onComponentAdded( Entity entity ) override;

      void update( float dt ) override;

   private:
      ComponentContainer<TimerComponent>* timersContainer = nullptr;
      GameContext* context_ = nullptr;
      bool started = false;

      static void updateTimer( float dt, TimerComponent& timer );
};
#endif //GAME1_TIMESYSTEM_H
