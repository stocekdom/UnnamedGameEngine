//
// Created by dominik on 09.12.25.
//

#ifndef GAME1_TIMERHANDLE_H
#define GAME1_TIMERHANDLE_H
#include <memory>

#include "Timer.h"

class TimerHandle
{
   public:
      explicit TimerHandle( const std::shared_ptr<Timer>& timer );

      [[nodiscard]] bool isValid() const;

      void stop() const;

      void pause() const;

      void unpause() const;

      void reset() const;

      [[nodiscard]] float getTimeLeft() const;

      [[nodiscard]] float getTimeElapsed() const;

   private:
      std::weak_ptr<Timer> timer;
};
#endif //GAME1_TIMERHANDLE_H
