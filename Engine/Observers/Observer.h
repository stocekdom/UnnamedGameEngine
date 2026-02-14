//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_OBSERVER_H
#define GAME1_OBSERVER_H

#include "EventData.h"

class Observer
{
   public:
      virtual ~Observer() = default;

      virtual void notify( EventData data ) = 0;
};
#endif //GAME1_OBSERVER_H
