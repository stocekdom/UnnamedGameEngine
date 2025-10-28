//
// Created by dominik on 15.10.25.
//
#include "UpdateScoreboardObserver.h"

UpdateScoreboardObserver::UpdateScoreboardObserver( const std::shared_ptr<Scoreboard>& scoreboard ) : scoreboard( scoreboard )
{
}

void UpdateScoreboardObserver::notify( EventData data )
{
   if( std::holds_alternative<ScoreboardUpdateEventData>( data ) )
   {
      if( auto s = scoreboard.lock() )
      {
         auto& d = std::get<ScoreboardUpdateEventData>( data );
         s->addScore( d.points );
      }
   }
}

