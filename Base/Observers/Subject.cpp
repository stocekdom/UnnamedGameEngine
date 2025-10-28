//
// Created by dominik on 15.10.25.
//
#include "Subject.h"

void Subject::addObserver( const std::shared_ptr<Observer>& observer )
{
   observers.push_back( observer );
}

void Subject::notifyObservers( EventData data )
{
   for( auto& observer: observers )
      if( auto o = observer.lock() )
         o->notify( data );
}

