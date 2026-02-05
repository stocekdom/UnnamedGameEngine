//
// Created by dominik on 09.12.25.
//

#ifndef GAME1_TIMEMANAGER_H
#define GAME1_TIMEMANAGER_H

#include "TimerHandle.h"
#include <vector>

class TimesSystem
{
   using Callback = std::function<void()>;

   public:
      /**
       * Creates a onefold timer
       * @param duration Duration of the timer in seconds
       * @param callback A callback that is called when the timer finishes
       * @return A handle for the timer
       */
      TimerHandle makeTimer( float duration, Callback callback );

      /**
       * Creates a timer that is repeated
       * @param duration Duration of the timer in seconds
       * @param callback A callback that is called every time the timer finishes
       * @return A handle for the timer
       */
      TimerHandle makeRepeatingTimer( float duration, Callback callback );

      void update( float dt );

   private:
      std::vector<std::shared_ptr<TimerComponent>> timers;
};
#endif //GAME1_TIMEMANAGER_H