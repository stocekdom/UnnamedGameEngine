//
// Created by dominik on 09.10.25.
//

#ifndef GAME1_COMMAND_H
#define GAME1_COMMAND_H

class Command
{
   public:
      virtual ~Command() = default;

      virtual void execute() = 0;

      virtual void stop() = 0;

   private:
};

#endif //GAME1_COMMAND_H
