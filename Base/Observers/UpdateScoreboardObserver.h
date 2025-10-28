//
// Created by dominik on 15.10.25.
//

#ifndef GAME1_UPDATESCOREBOARDOBSERVER_H
#define GAME1_UPDATESCOREBOARDOBSERVER_H

#include <memory>
#include "Observer.h"
#include "../../Entities/Scoreboard.h"

class UpdateScoreboardObserver : public Observer
{
   public:
      explicit UpdateScoreboardObserver( const std::shared_ptr<Scoreboard>& scoreboard );

      void notify( EventData data ) override;

   private:
      std::weak_ptr<Scoreboard> scoreboard;
};
#endif //GAME1_UPDATESCOREBOARDOBSERVER_H
