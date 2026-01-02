//
// Created by dominik on 02.01.26.
//

#ifndef GAME1_SYSTEM_H
#define GAME1_SYSTEM_H

struct GameContext;

class System
{
   public:
      virtual ~System() = default;

      /**
       * Lifecycle hook called after all systems have been constructed.
       * Here all systems are alive, and it is safe to use them, but they might not contain any useful data yet
       * @param context The game context
       */
      virtual void init( GameContext* context ) = 0;

      /**
       * Lifecycle hook called when the game is starting
       * It's called before the first frame. Here systems can do necessary operations without having to do them in the first frame
       */
      virtual void onStart() = 0;

      virtual void update( float dt ) = 0;
};

#endif //GAME1_SYSTEM_H
