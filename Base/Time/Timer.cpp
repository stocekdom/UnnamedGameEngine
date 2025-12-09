//
// Created by dominik on 09.12.25.
//

#include "Timer.h"

#include <utility>

Timer::Timer( const float duration, Callback callback, bool isRepeated )
   : isRepeated( isRepeated ), timerDuration( duration ), callback( std::move( callback ) )
{
}

void Timer::update( float dt )
{
   if( !isActive || isPaused )
      return;

   timeAccumulator += dt;

   if( timeAccumulator >= timerDuration )
   {
      // Execute the callback when the timer finishes
      callback();

      if( isRepeated )
         timeAccumulator = 0.f;
      else
         isActive = false;
   }
}

void Timer::stop()
{
   isActive = false;
}

void Timer::pause()
{
   isPaused = true;
}

void Timer::unpause()
{
   isPaused = false;
}
