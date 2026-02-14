//
// Created by dominik on 02.01.26.
//

#ifndef GAME1_UICONTROLLER_H
#define GAME1_UICONTROLLER_H
#include "Controller.h"

/**
 * Specialized controller that handles passing mouse click and release events to UI, since UI is a top layer and needs to be handled first
 */
class UIController : public Controller
{
   public:
      explicit UIController( GameContext* context );

      bool handleInput( const sf::Event& event ) override;

      void tick( float dt ) override;

   private:
      bool onLeftClick( const sf::Vector2i& position ) const;
};
#endif //GAME1_UICONTROLLER_H
