//
// Created by dominik on 15.11.25.
//

#ifndef GAME1_INPUTSYSTEM_H
#define GAME1_INPUTSYSTEM_H

#include "../System.h"
#include "Controller.h"
#include <vector>
#include <memory>

class InputSystem : public System
{
   public:
      explicit InputSystem() = default;

      void init( GameContext* context ) override;

      void onStart() override;

      void update( float dt ) override;

      void handleInput( const sf::Event& event ) const;

      void setUIController( std::unique_ptr<Controller> controller );

      void registerController( std::unique_ptr<Controller> controller );

      [[nodiscard]] const std::vector<std::unique_ptr<Controller>>& getControllers() const;

   private:
      // TODO chain of responsibility pattern in the future
      std::vector<std::unique_ptr<Controller>> controllers;
      /**
       * A controller called to handle input before any other controllers.
       * Ensures a proper UI response without propagating input to the other gameplay controllers
       * Example: If a player clicks an object behind some UI, the UI is clicked and the object is not
       */
      std::unique_ptr<Controller> uiController;
};

#endif //GAME1_INPUTSYSTEM_H
