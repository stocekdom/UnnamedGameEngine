//
// Created by dominik on 09.10.25.
//

#ifndef GAME1_BOWCONTROLLER_H
#define GAME1_BOWCONTROLLER_H

#include <memory>
#include <unordered_map>
#include "IController.h"
#include "../Entities/Bow.h"
#include "Commands/Command.h"

class BowController : public IController
{
   public:
      explicit BowController( const std::shared_ptr<Bow>& bow );

      void handleInput( const sf::Event& event ) override;

   private:

      void executeKeyboard( sf::Event event );

      void executeMouse( sf::Event event );

      // TODO Specialized controllers for entities and keyboardCommands need the specific type inside a constructor
      // For extensibility and reusability use casting, templates or components
      // This is the closest to Unreal Engine
      std::weak_ptr<Bow> pawn;
      std::unordered_map<sf::Keyboard::Key, std::unique_ptr<Command>> keyboardCommands;
      std::unordered_map<sf::Mouse::Button, std::unique_ptr<Command>> mouseCommands;
};

#endif //GAME1_BOWCONTROLLER_H
