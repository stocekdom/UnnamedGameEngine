//
// Created by dominik on 09.12.25.
//

#ifndef GAME1_TIMER_COMPONENT_H
#define GAME1_TIMER_COMPONENT_H
#include <functional>

struct TimerComponent
{
   using Callback = std::function<void()>;

   public:
      TimerComponent( const float duration, Callback callback, bool isRepeated )
         : isRepeated( isRepeated ), timerDuration( duration ), callback( std::move( callback ) )
      {
      }

      void stop()
      {
         isActive = false;
      }

      void pause()
      {
         isPaused = true;
      }

      void unpause()
      {
         isPaused = false;
      }

      void reset()
      {
         timeAccumulator = 0.f;
         isActive = true;
         isPaused = false;
      }

      [[nodiscard]] bool isTimerActive() const
      {
         return !isActive;
      }

      [[nodiscard]] bool isTimerPaused() const
      {
         return isPaused;
      }

      [[nodiscard]] float getTimeLeft() const
      {
         return timerDuration - timeAccumulator;
      }

      [[nodiscard]] float getTimeElapsed() const
      {
         return timeAccumulator;
      }

   private:
      bool isPaused = false;
      bool isActive = true;
      bool isRepeated = false;
      float timeAccumulator = 0.0f;
      float timerDuration;
      Callback callback;

      friend class TimeSystem;
};
#endif //GAME1_TIMER_COMPONENT_H
