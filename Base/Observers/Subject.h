//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_SUBJECT_H
#define GAME1_SUBJECT_H

#include <vector>
#include <memory>
#include "Observer.h"

class Subject
{
   public:
      void addObserver( const std::shared_ptr<Observer>& observer );

   protected:
      void notifyObservers( EventData data ) const;

   private:
      std::vector<std::weak_ptr<Observer>> observers;
};

#endif //GAME1_SUBJECT_H
