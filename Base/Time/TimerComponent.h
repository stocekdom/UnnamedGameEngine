//
// Created by dominik on 09.12.25.
//

#ifndef GAME1_TIMER_H
#define GAME1_TIMER_H
#include <functional>

class Timer
{
   using Callback = std::function<void()>;

   public:
      Timer( float duration, Callback callback, bool isRepeated = false );

      /**
       * Updates the timer with a given time
       * @param dt Amount of time to update
       * @return True if the timer is finished, false otherwise
       */
      void update( float dt );

      void stop();

      void pause();

      void unpause();

      bool isPaused = false;
      bool isActive = true;
      bool isRepeated = false;
      float timeAccumulator = 0.0f;
      const float timerDuration;

   private:
      Callback callback;
};
#endif //GAME1_TIMER_H
