//
// Created by dominik on 09.12.25.
//

#include "TimesSystem.h"

TimerHandle TimesSystem::makeTimer( float duration, Callback callback )
{
   const auto timer = std::make_shared<TimerComponent>( duration, std::move( callback ) );
   timers.push_back( timer );
   return TimerHandle( timer );
}

TimerHandle TimesSystem::makeRepeatingTimer( float duration, Callback callback )
{
   const auto timer = std::make_shared<TimerComponent>( duration, std::move( callback ), true );
   timers.push_back( timer );
   return TimerHandle( timer );
}

void TimesSystem::update( float dt )
{
   for( int i = 0; i < timers.size(); ++i )
   {
      timers[ i ]->update( dt );

      // Remove timers that finished or we stopped by TimerHandle
      if( timers[ i ]->isActive == false )
      {
         // Swap and pop - O(1)
         std::swap( timers[ i ], timers.back() );
         timers.pop_back();
      }
   }
}
