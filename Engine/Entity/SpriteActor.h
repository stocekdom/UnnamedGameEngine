//
// Created by dominik on 23.12.25.
//

#ifndef GAME1_SPRITEACTOR_H
#define GAME1_SPRITEACTOR_H
#include "Actor.h"

class SpriteActor : public Actor
{
   public:
      SpriteActor( REQ_ARGS, const std::string& texturePath, const ActorParams& params = ActorParams(),
                   SpriteMobility mobility = SpriteMobility::STATIC );
};

#endif //GAME1_SPRITEACTOR_H
