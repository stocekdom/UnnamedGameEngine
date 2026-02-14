//
// Created by dominik on 09.12.25.
//

#include "TimeSystem.h"
#include "../GameContext.h"

void TimeSystem::init( GameContext* context )
{
   context_ = context;
   context->scene->getComponentRegistry().registerComponentType<TimerComponent>();
   timersContainer = context->scene->getComponentRegistry().getComponentContainer<TimerComponent>();
}

void TimeSystem::onStart()
{
   for( auto& timer: *timersContainer )
      timer.reset();
}

void TimeSystem::onBeforeComponentsDestroyed( Entity entity )
{
}

void TimeSystem::onComponentAdded( Entity entity )
{
}

void TimeSystem::update( float dt )
{
   for( auto& timer: *timersContainer )
      updateTimer( dt, timer );

   // Remove inactive timers? They can be reset.
   /*
      // Remove timers that finished, or we stopped by TimerHandle
      if( timers[ i ]->isActive == false )
      {
         // Swap and pop - O(1)
         std::swap( timers[ i ], timers.back() );
         timers.pop_back();
      }*/
}

void TimeSystem::updateTimer( float dt, TimerComponent& timer )
{
   if( !timer.isActive || timer.isPaused )
      return;

   timer.timeAccumulator += dt;

   if( timer.timeAccumulator >= timer.timerDuration )
   {
      // Execute the callback when the timer finishes
      timer.callback();

      if( timer.isRepeated )
         timer.timeAccumulator = 0.f; // Or acc - dur?? try
      else
         timer.isActive = false;
   }
}
