//
// Created by dominik on 15.11.25.
//

#ifndef GAME1_INPUTSYSTEM_H
#define GAME1_INPUTSYSTEM_H

#include <vector>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "Controller.h"

class InputSystem
{
   public:
      explicit InputSystem() = default;

      virtual ~InputSystem() = default;

      void update( float dt );

      void handleInput( sf::Event event );

      void registerController( std::unique_ptr<Controller> controller );

      [[nodiscard]] const std::vector<std::unique_ptr<Controller>>& getControllers() const;

   private:
      // TODO chain of responsibility pattern in the future
      std::vector<std::unique_ptr<Controller>> controllers;
};

#endif //GAME1_INPUTSYSTEM_H
