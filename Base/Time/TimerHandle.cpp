//
// Created by dominik on 09.12.25.
//

#include "TimerHandle.h"

TimerHandle::TimerHandle( const std::shared_ptr<Timer>& timer )
{
}

bool TimerHandle::isValid() const
{
   return !timer.expired();
}

void TimerHandle::stop() const
{
   if( const auto t = timer.lock() )
      t->stop();
}

void TimerHandle::pause() const
{
   if( const auto t = timer.lock() )
      t->pause();
}

void TimerHandle::unpause() const
{
   if( const auto t = timer.lock() )
      t->unpause();
}

void TimerHandle::reset() const
{
   if( const auto t = timer.lock() )
   {
      t->timeAccumulator = 0.f;
      t->isActive = true;
      t->isPaused = false;
   }
}

float TimerHandle::getTimeLeft() const
{
   if( const auto t = timer.lock() )
      return t->timerDuration - t->timeAccumulator;

   return 0.f;
}

float TimerHandle::getTimeElapsed() const
{
   if( const auto t = timer.lock() )
      return t->timeAccumulator;

   return 0.f;
}
