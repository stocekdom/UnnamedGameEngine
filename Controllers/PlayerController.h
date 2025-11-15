//
// Created by dominik on 15.11.25.
//

#ifndef GAME1_PLAYERCONTROLLER_H
#define GAME1_PLAYERCONTROLLER_H

#include <memory>
#include "../Base/Input/Controller.h"
#include "../Base/Scene.h"

class PlayerController : public Controller
{
   public:
      explicit PlayerController( GameScene& gameScene );

   protected:
      void onLeftClick( const sf::Event& event );

   private:
      GameScene& scene;
};

#endif //GAME1_PLAYERCONTROLLER_H
