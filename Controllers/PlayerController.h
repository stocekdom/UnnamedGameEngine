//
// Created by dominik on 15.11.25.
//

#ifndef GAME1_PLAYERCONTROLLER_H
#define GAME1_PLAYERCONTROLLER_H

#include "../Base/Input/Controller.h"
#include "../Base/Scene.h"
#include <memory>

class PlayerController : public Controller
{
   public:
      explicit PlayerController( const std::shared_ptr<GameScene>& gameScene );

   protected:
      void onLeftClick( const sf::Event& event );

   private:
      std::shared_ptr<GameScene> scene;
};

#endif //GAME1_PLAYERCONTROLLER_H
