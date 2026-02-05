//
// Created by dominik on 23.12.25.
//

#include "SpriteActor.h"

#include "../Sprite/SpriteComponent.h"

SpriteActor::SpriteActor( Entity id, GameContext* context, const std::string& texturePath, const ActorParams& params,
                          SpriteMobility mobility )
   : Actor( id, context, params )
{
   context->scene->addComponent<SpriteComponent>( id, texturePath, mobility );
}
