//
// Created by dominik on 09.10.25.
//

#ifndef GAME1_BOWCOMMANDS_H
#define GAME1_BOWCOMMANDS_H

#include <memory>
#include "Command.h"
#include "../../Entities/Bow.h"

class RotateUp : public Command
{
   public:
      explicit RotateUp( const std::shared_ptr<Bow>& bow );

      void execute() override;

      void stop() override;

   private:
      std::weak_ptr<Bow> pawn;
};

class RotateDown : public Command
{
   public:
      explicit RotateDown( const std::shared_ptr<Bow>& bow );

      void execute() override;

      void stop() override;

   private:
      std::weak_ptr<Bow> pawn;
};

class Charging : public Command
{
   public:
      explicit Charging( const std::shared_ptr<Bow>& bow );

      void execute() override;

      void stop() override;

   private:
      std::weak_ptr<Bow> pawn;
};
#endif //GAME1_BOWCOMMANDS_H
